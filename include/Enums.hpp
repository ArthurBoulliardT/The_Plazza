/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Enums
*/

#pragma once

#include <string>

namespace plzz
{
    enum DishType
    {
        PI_REGINA = 1,
        PI_MARGARITA = 2,
        PI_AMERICANA = 4,
        PI_FANTASIA = 8,
        // bonus
        PI_NEPTUNE = 16,
        PA_SPAGHETTI = 32
    };

    enum DishSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum cookState
    {
        READY,
        WORKING,
        WAITING,
    };

    enum IngredientsName
    {
        DOE,
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOM,
        STEAK,
        EGGPLANT,
        GOAT_CHEESE,
        CHIEF_LOVE,
        TUNA, // bonus NEPTUNE
        SQUID, // bonus NEPTUNE
        MOZZARELLA // bonus NEPTUNE
    };
    std::string enumToString(const IngredientsName &ing);
    std::string enumToString(const DishType &type);
    std::string enumToString(const DishSize &size);
}
