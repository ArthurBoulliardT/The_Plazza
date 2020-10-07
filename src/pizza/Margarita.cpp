/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#include "Margarita.hpp"

namespace plzz
{
    static const int COOCKING_TIME = 1;

    Margarita::Margarita(int fd, DishSize size, double mult):
        Pizza(fd, PI_MARGARITA, size, mult * COOCKING_TIME)
    {
    }

    Margarita::~Margarita()
    {
    }

    bool Margarita::isEnoughIng(Ingredients &ings)
    {
        return ings.is(DOE) && ings.is(TOMATO) && ings.is(GRUYERE);
    }

    void Margarita::preparing(Ingredients &ings) const
    {
        ings.use(DOE);
        ings.use(TOMATO);
        ings.use(GRUYERE);
    }
}