/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#pragma once

#include "Pizza.hpp"

namespace plzz
{
    class Fantasia : public Pizza
    {
        public:
            Fantasia(int fd, DishSize size, double mult);
            ~Fantasia();

            void preparing(Ingredients &ings) const final;
            static bool isEnoughIng(Ingredients &ings);
    };
}
