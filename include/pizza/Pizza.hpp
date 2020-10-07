/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#pragma once

#include "Ingredients.hpp"
#include "Enums.hpp"
#include "Logs.hpp"
#include "Order.hpp"

namespace plzz
{
    class Pizza : public Order
    {
        public:
            Pizza(int fd, DishType type, DishSize size, double timeCooking);
            virtual ~Pizza() {};

            virtual void preparing(Ingredients &) const {};
    };
}