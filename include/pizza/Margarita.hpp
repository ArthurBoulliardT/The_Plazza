/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#pragma once

#include "Pizza.hpp"

namespace plzz
{
    class Margarita : public Pizza
    {
        public:
            Margarita(int fd, DishSize size, double mult);
            ~Margarita();

            void preparing(Ingredients &ings) const final;
            static bool isEnoughIng(Ingredients &ings);
    };
}
