/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Neptune
*/

#include "Neptune.hpp"

namespace plzz
{
    static const int COOCKING_TIME = 8;

    Neptune::Neptune(int fd, DishSize size, double mult):
        Pizza(fd, PI_NEPTUNE, size, mult * COOCKING_TIME)
    {
    }

    Neptune::~Neptune()
    {
    }

    bool Neptune::isEnoughIng(Ingredients &ings)
    {
        return ings.is(TUNA) && ings.is(SQUID) && ings.is(MOZZARELLA);
    }

    void Neptune::preparing(Ingredients &ings) const
    {
        ings.use(TUNA);
        ings.use(SQUID);
        ings.use(MOZZARELLA);
    }
}
