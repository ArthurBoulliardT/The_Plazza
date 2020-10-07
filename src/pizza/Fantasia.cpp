/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#include "Fantasia.hpp"

namespace plzz
{
    static const int COOCKING_TIME = 4;

    Fantasia::Fantasia(int fd, DishSize size, double mult):
        Pizza(fd, PI_FANTASIA, size, mult * COOCKING_TIME)
    {
    }

    Fantasia::~Fantasia()
    {
    }

    bool Fantasia::isEnoughIng(Ingredients &ings)
    {
        return ings.is(DOE) && ings.is(TOMATO) && ings.is(EGGPLANT) && ings.is(GOAT_CHEESE) && ings.is(CHIEF_LOVE);
    }

    void Fantasia::preparing(Ingredients &ings) const
    {
        ings.use(DOE);
        ings.use(TOMATO);
        ings.use(EGGPLANT);
        ings.use(GOAT_CHEESE);
        ings.use(CHIEF_LOVE);
    }
}
