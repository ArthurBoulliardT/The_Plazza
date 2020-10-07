/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#pragma once

#include "Enums.hpp"
#include "Ingredients.hpp"

const int BASIC_FD = -1;

namespace plzz
{
    class Order
    {
        public:
            Order(int fd, DishType type, DishSize size, double timeCooking);
            Order(const Order &);
            Order();
            virtual ~Order() {};

            int getFd() const noexcept { return _fd; };
            DishType getType() const noexcept { return _type; };
            DishSize getSize() const noexcept { return _size; };
            double getTimeCooking() const noexcept { return _timeCooking; };

            void setFd(int fd) noexcept { _fd = fd; };

            static bool isEnoughIng(DishType type, Ingredients &ings);
            virtual void preparing(Ingredients &) const {};
            void cooking() const;

            virtual Order &operator=(const Order &order);

        private:
            int _fd;
            DishType _type;
            DishSize _size;
            double _timeCooking;
    };
}

std::ostream &operator<<(std::ostream &stream, const plzz::Order &order);

/*

CLASS ORDER QUI ENREGISTRE LES COMMANDES (contient une pizza)
CLASS EDIBLE QUI EST UN CONTENEUR TEMPLATE DE CE QUE VEUT LE CLIENT: permet de contenir une pizza, mais aussi autre chose
OnlineOrder qui hérite de order, qui contient un sockFd pour ecrire sur le socket

*/