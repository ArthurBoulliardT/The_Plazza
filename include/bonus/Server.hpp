/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Server
*/

#pragma once

#include <list>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include "Logs.hpp"

static const int SELECT_ERROR = -1;
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR = -1;
static const int PID_ERROR = -1;
static const int READING_ERROR = -1;
static const int PROG_ERROR = 84;
static const int _EXIT_SUCCESS = 1;
static const int PROG_SUCCESS = 0;
static const int MAX_MSG = 512;
static const int MSG_SIZE = 4;
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

    // Errors

class NetworkError : public std::exception
{
    public:
        NetworkError(std::string const &message,
            std::string const &functionPart = "Unknown") noexcept : _message(message), _functionPart(functionPart) {};
        virtual ~NetworkError() = default;

        std::string const &getFunctionPart() const noexcept { return _functionPart; };
        virtual const char *what() const noexcept override { return _message.c_str(); };

    private:
        std::string _message; // exception.what() to write when catching the error
        std::string _functionPart; // for example -> getName, etc...
};

class ClientError : public NetworkError
{
    public:
        ClientError(std::string const &message,
            std::string const &functionPart = "Unknown") noexcept : NetworkError("Client Error: " + message, functionPart) {};
};

class ServerError : public NetworkError
{
    public:
        ServerError(std::string const &message,
            std::string const &functionPart = "Unknown") noexcept : NetworkError("Server Error: " + message, functionPart) {};
};

class SocketError : public NetworkError
{
    public:
        SocketError(std::string const &message,
            std::string const &functionPart = "Unknown") noexcept : NetworkError("Socket Error: " + message, functionPart) {};
};

// Sockets

const std::string NETWORK_FILE = "network.txt";

class Sockets : public logs::Logs
{
    public:
        Sockets(int sockFd);
        virtual ~Sockets() {};

        static int create();
        static void closeSocket(int sockFd);
        static void printInfoSocket(std::ostream &stream, SOCKADDR_IN &csin);
        static void setSockOpt(int sockFd);

    protected:
        int _sockFd;
};

// Client

class Client : public Sockets
{
    public:
        Client(int sockFd, std::string userName = "Anonymous", std::string password = "", std::list<std::string> dialogues = {}, std::list<std::string> responses = {});
        Client(const Client &client);
        virtual ~Client() {};

        Client &operator=(const Client &client);

        int getSockFd() const noexcept { return _sockFd; };
        std::string getUserName() const noexcept { return _userName; };
        std::string getPassword() const noexcept { return _password; };
        std::list<std::string> getDialogues() const noexcept { return _dialogues; };
        std::list<std::string> getResponses() const noexcept { return _responses; };

        std::string getFrontDialogue();
        std::string getBackDialogue();

        std::string getFrontResponse();
        std::string getBackResponse();


        void setSockFd(int sockFd) { _sockFd = sockFd; };
        void setUserName(std::string &username) { _userName = username; };
        void setPassword(std::string &password) { _password = password; };
        void setDialogues(std::list<std::string> &dialogues) { _dialogues = dialogues; };

        void cleanDialogues() noexcept { _dialogues.clear(); };

        void addDialogue(std::string &aDialogue) { _dialogues.emplace_back(aDialogue); };
        void addDialogue(std::list<std::string> &someDialogues);

        void addResponse(std::string &aResponse) { _responses.emplace_back(aResponse); };

        static bool writeSomethingFor(int aSockFd, std::string response);

    private:
        std::string _userName;
        std::string _password;
        std::list<std::string> _dialogues;
        std::list<std::string> _responses;
};

// Server

class Server : public Sockets
{
    public:
        Server(int port = 4242, int maxConnections = 5);
        virtual ~Server() {};

        void run();
        virtual bool loopServer();

        virtual void printInfoServer();

    protected:
        int _port;
        int _maxConnections;
        fd_set _activeFdSet;
        SOCKADDR_IN _serverAddr;
        std::list<Client> _clients;

        Client &getClientFrom(int aSockFd);
        void removeClient(int aSockFd);
        void removeClientFromList(int aSockFd);
        void socketReadingBehavior(int aSockFd);
        void parseReading(Client &client);
        virtual void useReading(std::list<std::string> &, int) {};

    private:
        void setSockOptSocketServer();
        void bindSocketServer();
        void listenSocketServer();
        void acceptConnection();

        void addClient(int aSockFd);

        void socketReading(int aSockFd);
        void socketWriting(int aSockFd);

};

