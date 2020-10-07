/*
** EPITECH PROJECT, 2020
** test_plazza
** File description:
** Thread
*/

#include "Thread.hpp"

namespace plzz {
    Thread::Thread() : _threading()
    {
    }

    Thread::~Thread()
    {
        std::cout << "thread destroyed" << std::endl;
    }

    void Thread::lock()
    {
        _mutex.lock();
    }

    void Thread::unlock()
    {
        _mutex.unlock();
    }

    void Thread::join()
    {
        _threading->join();
    }

    void Thread::detach()
    {
        _threading->detach();
    }
}