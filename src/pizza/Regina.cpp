/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Regina
*/

#include "Regina.hpp"

namespace plzz
{
    static const int COOCKING_TIME = 2;

    Regina::Regina(int fd, DishSize size, double mult):
        Pizza(fd, PI_REGINA, size, mult * COOCKING_TIME)
    {
    }

    Regina::~Regina()
    {
    }

    bool Regina::isEnoughIng(Ingredients &ings)
    {
        return ings.is(DOE) && ings.is(TOMATO) && ings.is(GRUYERE) && ings.is(HAM) && ings.is(MUSHROOM);
    }

    void Regina::preparing(Ingredients &ings) const
    {
        ings.use(DOE);
        ings.use(TOMATO);
        ings.use(GRUYERE);
        ings.use(HAM);
        ings.use(MUSHROOM);
    }
}
