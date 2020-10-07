/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#include "Order.hpp"
#include "Regina.hpp"
#include "Margarita.hpp"
#include "Fantasia.hpp"
#include "Americana.hpp"
#include "Neptune.hpp"

namespace plzz
{
    Order::Order(int fd, DishType type, DishSize size, double timeCooking):
        _fd(fd),
        _type(type),
        _size(size),
        _timeCooking(timeCooking)
    {
    }

    Order::Order(const Order &order):
        _fd(order._fd),
        _type(order._type),
        _size(order._size),
        _timeCooking(order._timeCooking)
    {
    }

    Order::Order():
        _fd(0),
        _type(DishType::PI_REGINA),
        _size(DishSize::S),
        _timeCooking(0)
    {
    }

    void Order::cooking() const
    {
        auto time = std::chrono::milliseconds((int)(_timeCooking * 1000));

        std::this_thread::sleep_for(time);
    }

    Order &Order::operator=(const Order &order)
    {
        _fd = order._fd;
        _type = order._type;
        _size = order._size;
        _timeCooking = order._timeCooking;
        return *this;
    }

    bool Order::isEnoughIng(DishType type, Ingredients &ings)
    {
        bool isEnoughOfIt = false;

        switch (type)
        {
        case PI_REGINA:
            isEnoughOfIt = Regina::isEnoughIng(ings);
            break;
        case PI_MARGARITA:
            isEnoughOfIt = Margarita::isEnoughIng(ings);
            break;
        case PI_FANTASIA:
            isEnoughOfIt = Fantasia::isEnoughIng(ings);
            break;
        case PI_AMERICANA:
            isEnoughOfIt = Americana::isEnoughIng(ings);
            break;
        case PI_NEPTUNE:
            isEnoughOfIt = Neptune::isEnoughIng(ings);
            break;
        default:
            break;
        }
        return isEnoughOfIt;
    }

}

std::ostream &operator<<(std::ostream &stream, const plzz::Order &order)
{
    return stream << order.getFd() << " client ordered " << enumToString(order.getType()) << " " << enumToString(order.getSize());
}