/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** PlazzaServer
*/

#include "PlazzaServer.hpp"
#include "Receptionist.hpp"

namespace plzz
{
    PlazzaServer::PlazzaServer(Receptionist &reception):
        Server(),
        _receptionist(reception)
    {
    }

    PlazzaServer::~PlazzaServer()
    {
    }

    void PlazzaServer::printInfoServer()
    {
        output("You can order on this online server, free delivery with amazon prime!");
        Sockets::printInfoSocket(std::cout, _serverAddr);
    }

    void PlazzaServer::useReading(std::list<std::string> &inputs, int aSockFd)
    {
        _receptionist.lock();
        _receptionist.addOnlineOrders(inputs, aSockFd);
        _receptionist.unlock();
    }
}
