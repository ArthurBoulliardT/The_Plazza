/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#pragma once

#include <iostream>
#include "Ingredients.hpp"
#include "Order.hpp"
#include "Logs.hpp"
#include "Enums.hpp"
#include "Thread.hpp"

namespace plzz {
    class Kitchen;

    class Cook : public logs::Logs, public Thread {
        public:
            Cook(int id, Kitchen &kitchen);
            ~Cook();
            void run();
            void cooking(Ingredients &ing, std::unique_ptr<Order> &order);

        private:
            int _id;
            Thread _writeThread;
            Kitchen &_kitchen;
    };
}
