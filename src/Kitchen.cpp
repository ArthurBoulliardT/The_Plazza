/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "PackageMessage.hpp"
#include "Kitchen.hpp"

namespace plzz {
    Kitchen::Kitchen(int cookNbr, int id, int idReceptionist, unsigned long refreshingTime):
            Logs(LOGS_FILE),
            Thread(),
            _cookNbr(cookNbr),
            _id(id),
            _idReceptionist(idReceptionist),
            _ing(refreshingTime),
            _cooksPool(_cookNbr),
            _timePoint(std::chrono::steady_clock::now()),
            _orders(),
            _ipc(id)
    {
        file(id, "Creating a Kitchen ");
        _cooksPool.reserve(_cookNbr);
        setCooks();
        _id = id;
    }

    Kitchen::~Kitchen()
    {
    }

    void Kitchen::refreshTimePoint()
    {
        _timePoint = std::chrono::steady_clock::now();
    }

    void Kitchen::setCooks()
    {
        try {
            for (int i = 0; i < _cookNbr ;i++) {
                _cooksPool.insert({i, std::make_pair(READY, std::make_unique<Cook>(i, *this))});//creation cook
            }
        }
        catch (const std::exception &e) {
            std::cout << "exception cook creation " << e.what() << std::endl;
        }
        debug("Recruiting " + std::to_string(_cookNbr) + " cooks");
    }

    size_t Kitchen::getNbrReadyCooks() const noexcept
    {
        int nbr = 0;

        for (auto &cook: _cooksPool) {
            if (cook.second.first == READY)
                nbr++;
        }
        return nbr;
    }

    int Kitchen::ordersPlace() const noexcept
    {
        return (_cookNbr*2) - _orders.size();
    }

    void Kitchen::switchStateReady(unsigned int id)
    {
        if (id < _cooksPool.size()) {
            refreshTimePoint();
            _cooksPool[id].first = READY;
        }
    }

    void Kitchen::switchStateWorking(unsigned int id)
    {
        if (id < _cooksPool.size() ) {
            refreshTimePoint();
            _cooksPool[id].first = WORKING;
        }
    }

    void Kitchen::addOrder(Order &orders)
    {
        _orders.emplace(std::make_unique<Order>(orders));
    }

    std::unique_ptr<Order> &Kitchen::getFrontOrder()
    {
        auto &frontOrder = _orders.front();

        return frontOrder;
    }

    std::unique_ptr<Order> &Kitchen::getBackOrder()
    {
        auto &backOrder = _orders.back();

        return backOrder;
    }

    void Kitchen::shouldDeleteKitchen()
    {
        if (getNbrReadyCooks() == _cooksPool.size()) {
            auto current_time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(current_time - _timePoint) >= std::chrono::seconds(TIME_DIED_KITCHEN)){
                deleteKitchen();
                _quit = true;
            }
        }
    }

    void Kitchen::deleteKitchen()
    {
        _ipc.sendMessage(_id, "died", CHANNEL_DIED);
        debug("Deleting kitchen " + std::to_string(_id) + " say to " + std::to_string(_idReceptionist));
        file(_id, "deleting Kitchen with id ");
    }

    void Kitchen::run()
    {
        refreshTimePoint();
        debug("Kitchen " + std::to_string(_id) + " -> Hello");
        while (!_quit) {
            shouldDeleteKitchen();
            if (msgrcv(_ipc.getId(), &packetMessage, sizeof(packetMessage), 1, IPC_NOWAIT) < 0)
                continue;
            std::string command = std::string(packetMessage.mesg_text);
            if (command == "order") {
                Order order = packetMessage.order;
                addOrder(order);
            }
            if (command == "state") {
                _ipc.sendMessage(_idReceptionist, "stateReply:" + std::to_string(ordersPlace()), CHANNEL_STANDARD);
            }
        }
    }
}