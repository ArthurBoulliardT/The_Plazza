/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredients
*/

#include "Error.hpp"
#include "Ingredients.hpp"

namespace plzz
{
    Ingredients::Ingredients(unsigned long refreshTime):
        Logs(LOGS_FILE),
        _thread(),
        _quit(false),
        _refreshTime(refreshTime)
    {
        _thread.init(&Ingredients::increaseStock, this);
    }

    Ingredients::~Ingredients()
    {
        output("Ingredients destroyed");
    }

    void Ingredients::stop()
    {
        _quit = true;
    }

    void Ingredients::upOneIngs()
    {
        debug("Kitchen restocking");
        _ing[DOE] += 1;
        _ing[TOMATO] += 1;
        _ing[GRUYERE] += 1;
        _ing[HAM] += 1;
        _ing[MUSHROOM] += 1;
        _ing[STEAK] += 1;
        _ing[EGGPLANT] += 1;
        _ing[GOAT_CHEESE] += 1;
        _ing[CHIEF_LOVE] += 1;
        _ing[TUNA] += 1;
        _ing[SQUID] += 1;
        _ing[MOZZARELLA] += 1;
    }

    void Ingredients::increaseStock()
    {
        while (!_quit) {
            std::this_thread::sleep_for(_refreshTime);
            // _thread.secureModifVar([this](){
                this->upOneIngs();
            // });
        }
    }

    void Ingredients::use(IngredientsName ing, unsigned long units)
    {
        unsigned long ingUnits = _ing[ing];

        if (ingUnits > units) {
            _ing[ing] -= units;
        }
        else {
            throw KitchenError("Not enough " + enumToString(ing));
        }
    }

    bool Ingredients::is(IngredientsName ing)
    {
        unsigned long ingUnits = _ing[ing];

        return ingUnits > 0;
    }
}
