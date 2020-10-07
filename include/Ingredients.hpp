/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredients
*/

#pragma once

#include <unordered_map>
#include <chrono>
#include "Thread.hpp"
#include "Enums.hpp"
#include "Logs.hpp"

namespace plzz
{
    class Ingredients : public Thread, public logs::Logs {
        public:
            Ingredients(unsigned long refreshTime);
            ~Ingredients();
            void stop();
            void increaseStock();
            std::unordered_map<IngredientsName, unsigned long> getStock() { return _ing; };
            void use(IngredientsName ing, unsigned long units = 1);
            bool is(IngredientsName ing);

        private:
            Thread _thread;
            bool _quit = false;
            std::chrono::milliseconds _refreshTime;
            std::unordered_map<IngredientsName, unsigned long> _ing =
                {
                    {DOE, 5},
                    {TOMATO, 5},
                    {GRUYERE, 5},
                    {HAM, 5},
                    {MUSHROOM, 5},
                    {STEAK, 5},
                    {EGGPLANT, 5},
                    {GOAT_CHEESE, 5},
                    {CHIEF_LOVE, 5},
                    {TUNA, 5}, // bonus
                    {SQUID, 5}, // bonus
                    {MOZZARELLA, 5} // bonus
                };

            void upOneIngs();
    };
}