/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Socket
*/

#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "Config.hpp"

namespace plzz
{
    class Socket {
        public:
            Socket(unsigned int port = PORT, unsigned int maxClient = 42);
            Socket(const Socket &src):
                _port(),
                _max_clients(),
                _address(),
                _readfds(),
                _client_socket(),
                _master_socket(),
                _addrlen()
            {
                _client_socket = new unsigned int(*(src._client_socket));
            }

            ~Socket();

            void createMasterSocket();
            void setAddressMasterSocket();
            void runSocket();
            void runServer();
            void eventMaster();
            void eventSlave();

            Socket &operator=(const Socket &src)
            {
                _client_socket = new unsigned int(*(src._client_socket));
                return *this;
            }
        protected:
        private:
            int _port;
            unsigned int _max_clients;
            struct sockaddr_in _address;
            fd_set _readfds;
            unsigned int *_client_socket;
            int _master_socket;
            int _addrlen;
            char _buffer[BUFFER_SIZE];
    };
}