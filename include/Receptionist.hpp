/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Receptionist
*/

#pragma once
#include <unistd.h>
#include <vector>
#include <regex>
#include <list>
#include "Order.hpp"
#include "Kitchen.hpp"
#include "Regina.hpp"
#include "Margarita.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"
#include "Neptune.hpp"
#include "Config.hpp"
#include "IPC.hpp"

namespace plzz
{
    class Receptionist : public logs::Logs, public Thread
    {
        public:
            Receptionist(double ckMult, unsigned long cooksNb, unsigned long refreshingTime);
            ~Receptionist();

            void openRestaurant();
            static std::list<std::string> interpretAnOrder(const std::string &order, std::regex orderRegex = std::regex("([a-zA-Z]+) (S|M|L|XL|XXL) (x[1-9][0-9]*)"));
            void addOnlineOrders(std::list<std::string> &inputs, int aSockFd);

        private:
            static inline std::regex _orderRegex = std::regex("([a-zA-Z]+) (S|M|L|XL|XXL) (x[1-9][0-9]*)");
            static inline int _uid = BEGIN_UID;
            double _cookingMult;
            unsigned long _cooksNb;
            unsigned long _refreshIngTime;
            std::queue<std::unique_ptr<Order>> _orders;
            std::vector<int>_kitchensList;
            IPC _ipc;
            Thread _thread;
            std::vector<std::string>splitString(std::string command, char delim);

            void printPrompt() const noexcept { std::cout << "Please order something:" << std::endl; };
            void readInput();
            bool interpretOrder(const std::string &order);
            void handleKitchens(std::unique_ptr<plzz::Order> &order);
            std::vector<Order> treatAnOrder(const std::string &pizzaType, const std::string &DishSize, const std::string &numberOfPizza);

            void addAnOrderToQueue(Order &order);
            void addAnOrderToQueue(std::vector<Order> &orders);
            void addAnOrderToQueue(const std::string &DishType, const std::string &DishSize, const std::string &numberOfPizza);
            void addAnOrderToQueue(int aSockFd, const std::string &DishType, const std::string &DishSize, const std::string &numberOfPizza);    

            unsigned long getNumberOfOrder(const std::string &numberOfOrder) const;
            DishType getDishTypeFromString(const std::string &DishType) const;
            DishSize getDishSizeFromString(const std::string &DishSize) const;

            Order createAnOrder(DishType, DishSize);
            void createKitchen(int id);
            void updateKitchensAlive();
            int parseKitchenResponses();
            void putOrderForKitchen(int id, std::unique_ptr<plzz::Order> &order);
            void dispatchOrderToKitchen();

            void launchPlazzaServer();
            int foundFreeKitchen();
    };
}
