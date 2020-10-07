/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Receptionist
*/

#include "PackageMessage.hpp"
#include "Receptionist.hpp"
#include "PlazzaServer.hpp"
#include <sstream>

namespace plzz
{
    Receptionist::Receptionist(double ckMult, unsigned long cooksNb, unsigned long refreshingTime):
        Logs(LOGS_FILE),
        Thread(),
        _cookingMult(ckMult),
        _cooksNb(cooksNb),
        _refreshIngTime(refreshingTime),
        _orders(),
        _kitchensList(),
        _ipc(0),
        _thread()
    {
        init(&Receptionist::launchPlazzaServer, this);
        _thread.init(&Receptionist::dispatchOrderToKitchen, this);
    }

    Receptionist::~Receptionist()
    {
    }

    void Receptionist::launchPlazzaServer()
    {
        try {
            PlazzaServer plazzaServer(*this);

            plazzaServer.run();
        }
        catch (const ServerError &e) {
            file("Server not disponible for the moment");
            sleep(1);
            launchPlazzaServer();
        }
    }

    std::list<std::string> splitAString(std::string command, char delim)
    {
        std::list<std::string> strings;
        std::istringstream fileStream(command);
        std::string s;

        while (getline(fileStream, s, delim))
            strings.emplace_back(s);
        return strings;
    }

    void Receptionist::addOnlineOrders(std::list<std::string> &inputs, int aSockFd)
    {
        for (auto &order: inputs) {
            std::list<std::string> theSplitString = splitAString(order, ' ');

            std::string type = theSplitString.front();
            theSplitString.pop_front();

            std::string size = theSplitString.front();
            theSplitString.pop_front();

            std::string number = theSplitString.front();
            theSplitString.pop_front();

            addAnOrderToQueue(aSockFd, type, size, number);
        }
    }

    unsigned long Receptionist::getNumberOfOrder(const std::string &numberOfOrder) const
    {
        auto it = std::find_if(numberOfOrder.begin()+1, numberOfOrder.end(), [] (const char &c) {
            return c < '0' || '9' < c;
        });
        if (it == numberOfOrder.end())
            return std::atoi((numberOfOrder.c_str()+1));
        throw PizzaError("Bad number of pizza");
    }

    DishType Receptionist::getDishTypeFromString(const std::string &dishType) const
    {
        std::string theDishType = dishType;
        std::vector<std::pair<std::string, DishType>> types = {
            {"regina", PI_REGINA},
            {"margarita", PI_MARGARITA},
            {"americana", PI_AMERICANA},
            {"fantasia", PI_FANTASIA},
            {"neptune", PI_NEPTUNE}
            };

        std::for_each(theDishType.begin(), theDishType.end(), [](char & c) {
            c = ::tolower(c);
        });
        for (auto &aType : types) {
            if (theDishType == aType.first) {
                return aType.second;
            }
        }
        throw PizzaError("Unknow type of pizza named : " + dishType);
    }

    DishSize Receptionist::getDishSizeFromString(const std::string &dishSize) const
    {
        std::vector<std::pair<std::string, DishSize>> sizes = {
            {"S", S},
            {"M", M},
            {"L", L},
            {"XL", XL},
            {"XXL", XXL},
            };

        for (auto &aSize : sizes) {
            if (dishSize == aSize.first) {
                return aSize.second;
            }
        }
        throw PizzaError("Unknow size of pizza named : " + dishSize);
    }

    Order Receptionist::createAnOrder(DishType aType, DishSize aSize)
    {
        switch (aType)
        {
        case PI_REGINA:
            return Regina(BASIC_FD, aSize, _cookingMult);
            break;
        case PI_MARGARITA:
            return Margarita(BASIC_FD, aSize, _cookingMult);
            break;
        case PI_AMERICANA:
            return Americana(BASIC_FD, aSize, _cookingMult);
            break;
        case PI_FANTASIA:
            return Fantasia(BASIC_FD, aSize, _cookingMult);
            break;
        case PI_NEPTUNE:
            return Neptune(BASIC_FD, aSize, _cookingMult);
            break;
        default:
            throw PizzaError("Cannot create a pizza of type '" + enumToString(aType) + "'");
            break;
        }
    }

    std::vector<Order> Receptionist::treatAnOrder(  const std::string &dishType, 
                                                    const std::string &dishSize, 
                                                    const std::string &numberOfOrder)
    {
        std::vector<Order> orders;
        long i = getNumberOfOrder(numberOfOrder);
        DishType type = getDishTypeFromString(dishType);
        DishSize size = getDishSizeFromString(dishSize);

        file(   "Adding " + std::to_string(i)
                + " " + dishSize + " " + dishType + " order");
        while (i > 0) {
            orders.push_back(createAnOrder(type, size));
            i--;
        }
        return orders;
    }

    void Receptionist::addAnOrderToQueue(Order &order)
    {
        _orders.emplace(std::make_unique<Order>(order));
    }

    void Receptionist::addAnOrderToQueue(std::vector<Order> &orders)
    {
        for (auto &order: orders) {
            addAnOrderToQueue(order);
        }
        if (orders.at(0).getFd() == BASIC_FD) {
            output("Added " + std::to_string(orders.size()) + " " + enumToString(orders.at(0).getType()) + " orders");
        }
        else {
            output("Added " + std::to_string(orders.size()) + " " + enumToString(orders.at(0).getType()) + " orders for client " + std::to_string(orders.at(0).getFd()));
        }
    }

    void Receptionist::addAnOrderToQueue(   const std::string &dishType,
                                            const std::string &DishSize, 
                                            const std::string &numberOfPizza)
    {
        auto orders = treatAnOrder(dishType, DishSize, numberOfPizza);

        addAnOrderToQueue(orders);
    }    
    
    void Receptionist::addAnOrderToQueue(   int aSockFd,
                                            const std::string &dishType,
                                            const std::string &DishSize, 
                                            const std::string &numberOfPizza)
    {
        auto orders = treatAnOrder(dishType, DishSize, numberOfPizza);

        for (auto &order: orders) {
            order.setFd(aSockFd);
        }
        addAnOrderToQueue(orders);
    }

    std::list<std::string> Receptionist::interpretAnOrder(const std::string &order, std::regex orderRegex)
    {
        std::smatch matches;
        std::string match;
        std::string inputStr = order;
        std::list<std::string> orders;

        while (!inputStr.empty() && inputStr.size() > 2) {
            if (std::regex_search(inputStr, matches, orderRegex)) {
                orders.push_back(matches.str(0));
                inputStr = matches.suffix();
            }
            else {
                break;
            }
        }
        return orders;
    }

    bool Receptionist::interpretOrder(const std::string &order)
    {
        file(order, "\nReading input order line: ");
        try {
            std::smatch matches;
            std::string match;
            std::string inputStr = order;

            while (!inputStr.empty()) {
                if (std::regex_search(inputStr, matches, _orderRegex)) {
                    addAnOrderToQueue(matches.str(1), matches.str(2), matches.str(3));
                    inputStr = matches.suffix();
                }
                else {
                    throw ExecutionError("Input Error");
                }
            }
            return true;
        }
        catch (const PizzaError &e) {
            file(e.what());
            return true;
        }
        catch (const ExecutionError &e) {
            file(e.what());
            return true;
        }
        catch (const std::exception &e) {
            file(e.what());
            throw ExecutionError("Wrong behavior");
        }
    }

    void Receptionist::createKitchen(int id)
    {
        pid_t pid = fork();
        if (pid == 0) {
            file("Created Kitchen" + std::to_string(id));
            Kitchen kit(_cooksNb, id, _ipc.getId(), _refreshIngTime);
            kit.run();
            exit(0);
        }
    }

    void Receptionist::dispatchOrderToKitchen()
    {
        while (1) {
            if (_orders.size() > 0) {
                debug("New pizza detected");
                std::unique_ptr<plzz::Order> theOrder;
                theOrder.swap(_orders.front());
                updateKitchensAlive();
                handleKitchens(theOrder);
                _orders.pop();
            }
            sleep(TIME_SLEEP);
        }
    }

    void Receptionist::readInput()
    {
        std::string input;
        fd_set readInputFd;
        int result;

        FD_ZERO(&readInputFd);
        FD_SET(STDIN_FILENO, &readInputFd);
        try {
            printPrompt();
            while (std::cin.eof() == 0) {
                result = select(1, &readInputFd, nullptr, nullptr, nullptr);
                if (result != -1) {
                    if (FD_ISSET(STDIN_FILENO, &readInputFd))
                    {
                        std::getline(std::cin, input);
                        if (!input.empty()) {
                            if (input == "finish" || input == "quit") {
                                break;
                            }
                            if (!interpretOrder(input))
                                break;
                        }
                        printPrompt();
                    }
                }
                else {
                    error("The receptionist will be back in a minute");
                    break;
                }
            }
        }
        catch (const std::exception &e) {
            throw ExecutionError(e.what());
        }
    }

    void Receptionist::putOrderForKitchen(int id, std::unique_ptr<plzz::Order> &order)
    {
        _ipc.sendMessageWithOrder(id, "order", order);
    }

    void Receptionist::updateKitchensAlive()
    {
        for (size_t i = 0; i != _kitchensList.size(); i++) {
            if (msgrcv(_kitchensList[i], &packetMessage, sizeof(packetMessage), CHANNEL_DIED, IPC_NOWAIT) > 0) {
                std::string command = std::string(packetMessage.mesg_text);
                if (command == "died") {
                    // std::cout << "Reception delete kitchen " << _kitchensList[i] << std::endl;
                    _kitchensList[i] = -1;
                }
            }
        }
        _kitchensList.erase(std::remove(_kitchensList.begin(), _kitchensList.end(), -1), _kitchensList.end());
    }

    int Receptionist::foundFreeKitchen()
    {
        for (auto &elem : _kitchensList) {
            _ipc.sendMessage(elem, "state", CHANNEL_STANDARD);
            msgrcv(_ipc.getId(), &packetMessage, sizeof(packetMessage), CHANNEL_STANDARD, WAITING_MESSAGE);
            auto freeSpacesKitchenParse = splitString(packetMessage.mesg_text, ':');
            int freeSpacesKitchen = std::stoi(freeSpacesKitchenParse[1]);
            if (freeSpacesKitchen > 0) {
                return elem;
            }
        }
        return -1;
    }

    void Receptionist::handleKitchens(std::unique_ptr<plzz::Order> &order)
    {
        int freeKitchenId = foundFreeKitchen();

        if (freeKitchenId == -1) {
            int channelIPC = msgget(_uid + KEYSHAREDMEMORY, IPC_CREAT | PERMISSION_IPC);
            _kitchensList.push_back(channelIPC);
            createKitchen(channelIPC);
            _uid++;
            freeKitchenId = channelIPC;
        }
        putOrderForKitchen(freeKitchenId, order);
    }

    void Receptionist::openRestaurant()
    {
        file("Starting program");
        file(_cookingMult, "Cooking mult = ");
        file(_cooksNb, "Cooks number = ");
        file(_refreshIngTime, "Refreshing time = ");
        readInput();
    }

    std::vector<std::string> Receptionist::splitString(std::string command, char delim)
    {
        std::vector<std::string> strings;
        std::istringstream f(command);
        std::string s;

        while (getline(f, s, delim)) {
            strings.push_back(s);
        }
        return strings;
    }

}