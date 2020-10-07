/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Regina
*/

#pragma once

#include "Pizza.hpp"

namespace plzz
{
    class Regina : public Pizza
    {
        public:
            Regina(int fd, DishSize size, double mult);
            ~Regina();

            void preparing(Ingredients &ings) const final;
            static bool isEnoughIng(Ingredients &ings);
    };
}
