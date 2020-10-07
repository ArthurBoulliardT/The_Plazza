/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Error
*/

#pragma once

#include <string>

class PlazzaErrors : public std::exception
{
    public:
        PlazzaErrors(std::string const &message,
                std::string const &functionPart = "Unknown") noexcept : _message(message), _functionPart(functionPart) {};
        virtual ~PlazzaErrors() = default;

        std::string const &getFunctionPart() const noexcept { return _functionPart; };
        virtual const char *what() const noexcept override { return _message.c_str(); };

    private:
        std::string _message; // exception.what() to write when catching the error
        std::string _functionPart; // for example -> getName, etc...
};

class PizzaError : public PlazzaErrors
{
    public:
        PizzaError(std::string const &message,
                std::string const &functionPart = "Unknown") noexcept : PlazzaErrors("Pizza Error: " + message, functionPart) {};
};

class IPCError : public PlazzaErrors
{
    public:
        IPCError(std::string const &message,
                std::string const &functionPart = "Unknown") noexcept : PlazzaErrors("IPC Error: " + message, functionPart) {};
};

class ReceptionError : public PlazzaErrors
{
    public:
        ReceptionError(std::string const &message,
                std::string const &functionPart = "Unknown") noexcept : PlazzaErrors("Reception Error: " + message, functionPart) {};
};

class KitchenError : public PlazzaErrors
{
    public:
        KitchenError(std::string const &message,
                std::string const &functionPart = "Unknown") noexcept : PlazzaErrors("Kitchen Error: " + message, functionPart) {};
};

class ExecutionError : public PlazzaErrors
{
    public:
        ExecutionError(std::string const &message) noexcept : PlazzaErrors("Execution Error: "+ message, "Execution") {};
};

class FileError: public PlazzaErrors
{
    public:
        FileError(std::string const &message) noexcept : PlazzaErrors("File Error: " + message, "FileContent") {};
};
