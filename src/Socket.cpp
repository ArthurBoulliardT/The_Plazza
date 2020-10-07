/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Socket
*/

#include "Socket.hpp"
#include "Logs.hpp"

namespace plzz
{
    Socket::Socket(unsigned int port, unsigned int maxClients):
        _port(),
        _max_clients(),
        _address(),
        _readfds(),
        _client_socket(),
        _master_socket(),
        _addrlen()
    {
        _max_clients = maxClients;
        _port = port;
        _client_socket = new unsigned int[maxClients];
        for (unsigned int i = 0; i < maxClients; i++)
            _client_socket[i] = 0;
        createMasterSocket();
        setAddressMasterSocket();
        runSocket();
    }

    Socket::~Socket()
    {
    }

    void Socket::createMasterSocket()
    {
        int setSocketReturn;
        int operation = true;

        _master_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(_master_socket == 0)
            throw("socket failed");
        setSocketReturn = setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&operation, sizeof(operation));
        if (setSocketReturn == -1)
            throw("setsockopt failed");
    }

    void Socket::setAddressMasterSocket()
    {
        int bindReturn;

        _address.sin_family = AF_INET;
        _address.sin_addr.s_addr = INADDR_ANY;
        _address.sin_port = htons(_port);
        bindReturn = bind(_master_socket, (struct sockaddr *)&_address, sizeof(_address));
        if (bindReturn == -1)
            throw("bind failed");
    }

    void Socket::runSocket()
    {
        int listenReturn = listen(_master_socket, SOMAXCONN);

        if (listenReturn == -1)
            throw("listen failed");
        std::cout << "Server running on port " << _port << std::endl;
        std::cout << "Waiting connection " << _port << std::endl;
        _addrlen = sizeof(_address);
    }

    void Socket::eventMaster()
    {
        int byte_send;
        int new_socket = accept(_master_socket, (struct sockaddr *)&_address, (socklen_t*)&_addrlen);

        if (new_socket == -1) {
            throw("accept failed");
        }
        logs::Logs::debug("New client");
        byte_send = send(new_socket, "welcome", 9, 0);
        if (byte_send != 9) {
            throw("send failed");
        }
        for (unsigned int i = 0; i < _max_clients; i++) {
            if (_client_socket[i] == 0) {
                _client_socket[i] = new_socket;
                break;
            }
        }
    }

    void Socket::eventSlave()
    {
        int sd;
        int byte_read;

        for (unsigned int i = 0; i < _max_clients; i++) {
            sd = _client_socket[i];
            if (FD_ISSET(sd , &_readfds)) {
                byte_read = read(sd , _buffer, BUFFER_SIZE);
                if (byte_read == 0) {
                    getpeername(sd , (struct sockaddr*)&_address , (socklen_t*)&_addrlen);
                    close(sd);
                    _client_socket[i] = 0;
                } else {
                    _buffer[byte_read] = '\0';
                    if (strncasecmp(_buffer, "stop", 4) == 0)
                        throw("Stop server");
                    send(sd, _buffer, strlen(_buffer), 0);
                    std::cout << "Reçu de " << sd << " " << _buffer << std::endl;
                }
            }
        }
    }

    void Socket::runServer()
    {
        int activity;
        int socket;
        int max_socket;

        while(1) {
            FD_ZERO(&_readfds);
            FD_SET(_master_socket, &_readfds); 
            max_socket = _master_socket; 

            for (unsigned int i = 0; i < _max_clients; i++) {
                socket = _client_socket[i];
                if (socket != -1)
                    FD_SET( socket , &_readfds);
                if (socket > max_socket)
                    max_socket = socket;
            }
            activity = select(max_socket + 1, &_readfds, nullptr, nullptr, nullptr);
            if ((activity < 0) && (errno!=EINTR)) {
                throw("select error");
            }
            if (FD_ISSET(_master_socket, &_readfds)) {
                eventMaster();
            }
            eventSlave();
        } 
    }
}
/*
int main()
{
    try {
        auto newClass = plzz::Socket(4242, 2323);
        newClass.runServer();
        // std::thread (pause_thread,1).detach();
    } catch(char const *e) {
        std::cout << e << std::endl;
    }
    return 0;
}
*/