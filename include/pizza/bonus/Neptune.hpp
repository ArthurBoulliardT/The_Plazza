/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Neptune
*/

#pragma once

#include "Pizza.hpp"

namespace plzz
{
    class Neptune : public Pizza
    {
        public:
            Neptune(int fd, DishSize size, double mult);
            ~Neptune();

            void preparing(Ingredients &ings) const final;
            static bool isEnoughIng(Ingredients &ings);
    };
}