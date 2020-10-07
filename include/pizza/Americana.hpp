/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#pragma once

#include "Pizza.hpp"

namespace plzz
{
    class Americana : public Pizza
    {
        public:
            Americana(int fd, DishSize size, double mult);
            ~Americana();

            void preparing(Ingredients &ings) const final;
            static bool isEnoughIng(Ingredients &ings);
    };
}
