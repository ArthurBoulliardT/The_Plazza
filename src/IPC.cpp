/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IPC
*/

#include <iostream>
#include <cstring>
#include "fcntl.h"
#include "sys/ipc.h"
#include "sys/msg.h"
#include "IPC.hpp"
#include "Error.hpp"
#include "PackageMessage.hpp"

namespace plzz {
    IPC::IPC(int id):
        _id(id)
    {
        if (_id == 0)
            openQueue();
        else
            _id = id;
    }

    IPC::~IPC()
    {
    }

    void IPC::openQueue()
    {
        int createId;

        createId = msgget(ID_RECEPTIONIST, IPC_CREAT | 0666);
        if (createId == -1) {
            throw IPCError("Error msgget");
        }
        _id = createId;
    }

    int IPC::sendMessage(int id, std::string message, int channel)
    {
        packetMessage.mesg_type = channel;
        memset(packetMessage.mesg_text, 0, BUFFER_SIZE);
        memmove(packetMessage.mesg_text, message.c_str(), message.size());
        return msgsnd(id, &packetMessage, sizeof(packetMessage), 0);
    }


    int IPC::sendMessageWithOrder(int id, std::string message, std::unique_ptr<plzz::Order> &order)
    {
        packetMessage.mesg_type = CHANNEL_STANDARD;
        memset(packetMessage.mesg_text, 0, BUFFER_SIZE);
        memmove(packetMessage.mesg_text, message.c_str(), message.size());
        auto getPtrOrder = *(order.get());
        packetMessage.order = getPtrOrder;
        return msgsnd(id, &packetMessage, sizeof(packetMessage), 0);
    }
}