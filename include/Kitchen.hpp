/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#pragma once

#include <unistd.h>
#include <queue>
#include "IPC.hpp"
#include "Thread.hpp"
#include "Cook.hpp"
#include "Logs.hpp"
#include "Ingredients.hpp"
#include "Order.hpp"
#include "Config.hpp"

namespace plzz {
    class Kitchen : public logs::Logs, public Thread
    {
        using idCook = unsigned int;

        public:
            Kitchen(int cookNbr, int id, int idReceptionist, unsigned long refreshingTime);
            ~Kitchen();
            size_t getNbrReadyCooks() const noexcept;
            void addOrder(Order &orders);
            void setCooks();
            void switchStateReady(unsigned int id);
            void switchStateWorking(unsigned int id);
            void run();
            int getId() const noexcept { return _id; };
            void refreshTimePoint();
            int ordersPlace() const noexcept;
            std::unique_ptr<Order> &getFrontOrder();
            std::unique_ptr<Order> &getBackOrder();
            void popOrder() { _orders.pop(); };
            std::queue<std::unique_ptr<Order>> &getOrders() { return _orders; };
            Ingredients &getIngredients() noexcept { return _ing; }; 

        private:
            bool _quit = false;
            int _cookNbr;
            int _id;
            int _idReceptionist;
            Ingredients _ing;
            std::unordered_map<idCook, std::pair<cookState, std::unique_ptr<Cook>>> _cooksPool;
            std::chrono::time_point<std::chrono::steady_clock> _timePoint;
            std::queue<std::unique_ptr<Order>> _orders;
            IPC _ipc;

            void shouldDeleteKitchen();
            void deleteKitchen();
    };
}