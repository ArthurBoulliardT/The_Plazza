/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#include "Americana.hpp"

namespace plzz
{
    static const int COOCKING_TIME = 2;

    Americana::Americana(int fd, DishSize size, double mult):
        Pizza(fd, PI_AMERICANA, size, mult * COOCKING_TIME)
    {
    }

    Americana::~Americana()
    {
    }

    bool Americana::isEnoughIng(Ingredients &ings)
    {
        return ings.is(DOE) && ings.is(TOMATO) && ings.is(GRUYERE) && ings.is(STEAK);
    }

    void Americana::preparing(Ingredients &ings) const
    {
        ings.use(DOE);
        ings.use(TOMATO);
        ings.use(GRUYERE);
        ings.use(STEAK);
    }
}
