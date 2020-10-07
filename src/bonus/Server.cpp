/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Server
*/

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Server.hpp"
#include "Receptionist.hpp"

// class Client
Client::Client(int sockFd, std::string userName, std::string password, std::list<std::string> dialogues, std::list<std::string> responses):
    Sockets(sockFd),
    _userName(userName),
    _password(password),
    _dialogues(dialogues),
    _responses(responses)
{
}

Client::Client(const Client &client):
    Sockets(client._sockFd),
    _userName(client._userName),
    _password(client._password),
    _dialogues(client._dialogues),
    _responses(client._responses)
{
}

Client &Client::operator=(const Client &client)
{
    _sockFd = client._sockFd;
    _userName = client._userName;
    _password = client._password;
    _dialogues = client._dialogues;
    _responses = client._responses;
    return *this;
}

std::string Client::getFrontDialogue()
{
    if (_dialogues.size() > 0) {
        auto firstDialogue(_dialogues.front());

        _dialogues.pop_front();
        return firstDialogue;
    }
    return "";
}

std::string Client::getBackDialogue()
{
    if (_dialogues.size() > 0) {
        auto lastDialogue(_dialogues.back());

        _dialogues.pop_back();
        return lastDialogue;
    }
    return "";
}

std::string Client::getFrontResponse()
{
    if (_responses.size() > 0) {
        auto firstResponse(_responses.front());

        _responses.pop_front();
        return firstResponse;
    }
    return "";
}

std::string Client::getBackResponse()
{
    if (_responses.size() > 0) {
        auto lastResponse(_responses.back());

        _responses.pop_back();
        return lastResponse;
    }
    return "";
}

void Client::addDialogue(std::list<std::string> &someDialogues)
{
    for (auto &dialogue: someDialogues)
        _dialogues.emplace_back(dialogue);
}

bool Client::writeSomethingFor(int aSockFd, std::string response)
{
    write(aSockFd, response.c_str(), response.size());
    return true;
    /*fd_set wfds;

    if (select(aSockFd+1, nullptr, &wfds, nullptr, nullptr) != SELECT_ERROR) {
        if (FD_ISSET(aSockFd, &wfds)) {
            if (response.size() > 0) {
                size_t retval = write(aSockFd, response.c_str(), response.size());
                if (retval != response.size())
                    throw ClientError("Writing message error for fd " + std::to_string(aSockFd));
                return true;
            }
        }
        else
            std::cout << response << "(for client " << aSockFd << ")" << std::endl;
    }
    return false;*/
}

// class Sockets

Sockets::Sockets(int sockFd):
    Logs(NETWORK_FILE),
    _sockFd(sockFd)
{
}

int Sockets::create()
{
    SOCKET sock_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (sock_fd == INVALID_SOCKET) {
        throw SocketError("Socket creation error");
    }
    return (sock_fd);
}

void Sockets::closeSocket(int sockFd)
{
    close(sockFd); 
}

void Sockets::printInfoSocket(std::ostream &stream, SOCKADDR_IN &csin)
{
    std::string buff(inet_ntoa(csin.sin_addr));
    unsigned short cport = ntohs(csin.sin_port);

    stream << "Connection parameters " << buff << ":" << cport << std::endl;
}

void Sockets::setSockOpt(int sockFd)
{
    int opt = 1;

    if (setsockopt( sockFd, 
                    SOL_SOCKET, 
                    SO_REUSEADDR | SO_REUSEPORT, 
                    &opt, sizeof(opt))) 
    { 
        throw SocketError("Socket option error");
    }
}

// class Server

Server::Server(int port, int maxConnections):
    Sockets(Sockets::create()),
    _port(port),
    _maxConnections(maxConnections),
    _activeFdSet(),
    _serverAddr(),
    _clients()
{
    FD_ZERO(&_activeFdSet);
    FD_SET(_sockFd, &_activeFdSet);
}

Client &Server::getClientFrom(int aSockFd)
{
    for (auto &client: _clients) {
        if (client.getSockFd() == aSockFd)
            return client;
    }
    throw ServerError("No sockets for fd " + std::to_string(aSockFd));
}

void Server::removeClientFromList(int aSockFd)
{
    std::list<Client> clients;

    for (auto &client : _clients) {
        if (client.getSockFd() != aSockFd) {
            clients.emplace_back(client);
        }
    }
    _clients = clients;
}

void Server::removeClient(int aSockFd)
{
    removeClientFromList(aSockFd);
    Sockets::closeSocket(aSockFd);
    FD_CLR(aSockFd, &_activeFdSet);
}

void Server::run()
{
    bool looping = true;

    bindSocketServer();
    listenSocketServer();
    printInfoServer();

    while (looping) {
        looping = loopServer();
    }
    Sockets::closeSocket(_sockFd);
}

bool Server::loopServer()
{
    fd_set rfds = _activeFdSet;
    fd_set wfds = _activeFdSet;

    if (select(FD_SETSIZE, &rfds, &wfds, nullptr, nullptr) == SELECT_ERROR)
        throw ServerError("Select server error");
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (FD_ISSET(i, &rfds)) {
            socketReading(i);
        }
        else if (FD_ISSET(i, &wfds)) {
            socketWriting(i);
        }
    }
    return true;
}

void Server::socketReading(int aSockFd)
{
    if (aSockFd == _sockFd) {
        acceptConnection();
    }
    else {
        socketReadingBehavior(aSockFd);
    }
}

void Server::socketReadingBehavior(int aSockFd)
{
    try {
        auto &client = getClientFrom(aSockFd);
        char buffer[MAX_MSG];
        int nbytes = read(aSockFd, buffer, MAX_MSG);

        if (nbytes > 0) {
            std::string clientWrote(buffer);
            client.cleanDialogues();
            std::replace(clientWrote.begin(), clientWrote.end(), '\n', ' ');
            std::replace(clientWrote.begin(), clientWrote.end(), '\r', ' ');
            client.addDialogue(clientWrote);
            if (::strncmp(clientWrote.c_str(), "bye", 3) == 0) {
                removeClient(aSockFd);
            }
            else {
                parseReading(client);
            }
        }
        else if (nbytes == 0) {
            FD_CLR(aSockFd, &_activeFdSet);
            Sockets::closeSocket(aSockFd);
        }
    }
    catch (const ServerError &e) {
        removeClient(aSockFd);
    }
}

void Server::parseReading(Client &client)
{
    std::string theDialogue = client.getFrontDialogue();
    std::string response;

    if (theDialogue.size() > 0) {
        auto newOrders = plzz::Receptionist::interpretAnOrder(theDialogue);
        if (newOrders.size() > 0) {
            response = "Your order have been taken\n";
            useReading(newOrders, client.getSockFd());
        }
    }
    else {
        response = "Sorry, repeat your answer please.\n";
    }
    client.addResponse(response);
}

void Server::socketWriting(int aSockFd)
{
    try {
        auto &client = getClientFrom(aSockFd);

        if (aSockFd != _sockFd) {
            auto response = client.getFrontResponse();
            if (response.size() > 0) {
                size_t retval = write(aSockFd, response.c_str(), response.size());
                if (retval != response.size())
                    throw ClientError("Writing message error for fd " + std::to_string(aSockFd));
            }
        }
    }
    catch (const ServerError &e) {
        removeClient(aSockFd);
    }
}

void Server::printInfoServer()
{
    Sockets::printInfoSocket(std::cout, _serverAddr);
}

void Server::setSockOptSocketServer()
{
    Sockets::setSockOpt(_sockFd);
}

void Server::bindSocketServer()
{
    int retval;

    _serverAddr.sin_family = PF_INET;
    _serverAddr.sin_port = htons(_port);
    _serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    retval = bind(_sockFd, (SOCKADDR *) &_serverAddr, sizeof _serverAddr);
    if (retval == SOCKET_ERROR)
        throw ServerError("Bind server error");
}

void Server::listenSocketServer()
{
    int retval = listen(_sockFd, _maxConnections);

    if (retval == SOCKET_ERROR)
        throw ServerError("Listen server error");
}

void Server::acceptConnection()
{
    SOCKET csockFd;
    SOCKADDR_IN csin;
    unsigned int sinsize = sizeof csin;

    csockFd = accept(_sockFd, (SOCKADDR *)&csin, &sinsize);
    if (csockFd == INVALID_SOCKET) {
        throw ServerError("Accep connection server error");
    }
    addClient(csockFd);
}

void Server::addClient(int aSockFd)
{
    Client client(aSockFd);
    std::string firstResponses("Welcome to 3 michelin star Plazza\nPlease order something.\n");

    client.addResponse(firstResponses);
    _clients.emplace_back(client);
    FD_SET(aSockFd, &_activeFdSet);
}
