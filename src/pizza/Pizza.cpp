/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include <thread>
#include <chrono>
#include "Pizza.hpp"

namespace plzz
{
    Pizza::Pizza(int fd, DishType type, DishSize size, double timeCooking):
        Order(fd, type, size, timeCooking)
    {
    }

}