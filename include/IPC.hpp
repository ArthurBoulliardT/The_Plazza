/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IPC
*/

#pragma once
#include <sys/ipc.h>
#include <sys/msg.h>
#include "pizza/Pizza.hpp"
#include "Error.hpp"
#include "Config.hpp"
#include "Order.hpp"


namespace plzz
{
    // static struct mesg_buffer {
    //     long mesg_type;
    //     char mesg_text[BUFFER_SIZE];
    //     plzz::Order order;
    // } packetMessage;

    class IPC {
        public:
            IPC(int id);
            ~IPC();
            void openQueue();
            int sendMessage(int id, std::string message, int channel);
            int sendMessageWithOrder(int id, std::string message, std::unique_ptr<plzz::Order> &order);
            int getId() { return _id; };
        private:
            int _id;
    };
}