/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** PlazzaServer
*/

#pragma once

#include "Server.hpp"

namespace plzz
{
    class Receptionist;
    class PlazzaServer : public Server
    {
        public:
            PlazzaServer(Receptionist &reception);
            ~PlazzaServer();

            void printInfoServer() final;
        protected:
            Receptionist &_receptionist;

            void useReading(std::list<std::string> &inputs, int aSockFd) final;
    };
}