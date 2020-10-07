/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Enums
*/

#include "Enums.hpp"

namespace plzz
{
    std::string enumToString(const DishSize &size)
    {
        std::string sizeStr;

        switch (size)
        {
        case S:
            sizeStr = "S";
            break;
        case M:
            sizeStr = "M";
            break;
        case L:
            sizeStr = "L";
            break;
        case XL:
            sizeStr = "XL";
            break;
        case XXL:
            sizeStr = "XXL";
            break;        
        default:
            sizeStr = "unknow";
            break;
        }
        return sizeStr;
    }

    std::string enumToString(const DishType &type)
    {
        std::string pizzaStr;

        switch (type)
        {
        case PI_REGINA:
            pizzaStr = "regina";
            break;
        case PI_MARGARITA:
            pizzaStr = "margarita";
            break;
        case PI_AMERICANA:
            pizzaStr = "americana";
            break;        
        case PI_FANTASIA:
            pizzaStr = "fantasia";
            break;
        case PI_NEPTUNE:
            pizzaStr = "neptune";
            break;
        default:
            pizzaStr = "unknow";
            break;
        }
        return pizzaStr;
    }

    std::string enumToString(const IngredientsName &ing)
    {
        std::string ingStr;

        switch (ing)
        {
        case DOE:
            ingStr = "doe";
            break;
        case TOMATO:
            ingStr = "tomato";
            break;
        case GRUYERE:
            ingStr = "gruyere";
            break;
        case HAM:
            ingStr = "ham";
            break;
        case MUSHROOM:
            ingStr = "mushroom";
            break;
        case STEAK:
            ingStr = "steak";
            break;
        case EGGPLANT:
            ingStr = "eggplan";
            break;
        case GOAT_CHEESE:
            ingStr = "goat cheese";
            break;        
        case CHIEF_LOVE:
            ingStr = "chief love";
            break;
        case TUNA:
            ingStr = "tuna";
            break;
        case SQUID:
            ingStr = "squid";
            break;
        case MOZZARELLA:
            ingStr = "mozzarella";
            break;
        default:
            ingStr = "unknow";
            break;
        }
        return ingStr;
    }
}