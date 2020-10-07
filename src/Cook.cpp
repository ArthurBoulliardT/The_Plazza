/*
** EPITECH PROJECT, 2020
** test_plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include "Kitchen.hpp"
#include "Server.hpp"

namespace plzz {
    Cook::Cook(int id, Kitchen &kitchen):
        Logs(LOGS_FILE),
        Thread(),
        _id(id),
        _writeThread(),
        _kitchen(kitchen)
    {
        _id = id;
        init(&Cook::run, this);
    }

    Cook::~Cook()
    {
    }

    void Cook::cooking(Ingredients &ing, std::unique_ptr<Order> &order)
    {
        _kitchen.switchStateWorking(_id);


        order->preparing(ing);

        file("Kitchen ID[" + std::to_string(_kitchen.getId()) + "] cooking a pizza: " + enumToString(order->getType()));

        order->cooking();

        if (order->getFd() == BASIC_FD) {
            file("Kitchen [" + std::to_string(_kitchen.getId()) + "] finish cooking " + enumToString(order->getType()));
        }
        else {
            _writeThread.init(&Client::writeSomethingFor, order->getFd(), "Your pizza " + enumToString(order->getType()) + " is ready\n");
            //Client::writeSomethingFor(order->getFd(), "Your pizza " + enumToString(order->getType()) + " is ready\n");
        }

        _kitchen.switchStateReady(_id);
    }

    void Cook::run()
    {
        while (1) {
            lock();
            if (_kitchen.getOrders().size() > 0) {
                auto &order = _kitchen.getFrontOrder();
                if (Order::isEnoughIng(order->getType(), _kitchen.getIngredients())) {
                    cooking(_kitchen.getIngredients(), order);
                    _kitchen.popOrder();
                }
            }
            unlock();
            sleep(TIME_SLEEP); // save CPU
        }
    }
}