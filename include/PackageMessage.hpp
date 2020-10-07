/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Structure
*/

#pragma once
#include "Config.hpp"
#include "Order.hpp"

static struct mesg_buffer {
    mesg_buffer(): mesg_type(), mesg_text() , order(){};
    long mesg_type;
    char mesg_text[BUFFER_SIZE];
    plzz::Order order;
} packetMessage;