/*
** EPITECH PROJECT, 2020
** test_plazza
** File description:
** Thread
*/

#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

namespace plzz {
    class Thread {
        public:
            Thread();
            virtual ~Thread();
            void join();
            void detach();
            void lock();
            void unlock();
            template<typename T, typename ...Args>
            void init(T aFunct, Args ...args) {
                _threading = std::make_unique<std::thread>(std::thread(aFunct, args...));
                detach();
            }
            template<typename T>
            void secureModifVar(T aFunct) {
                lock();
                aFunct();
                unlock();
            }
        private:
            static inline std::mutex _mutex = {};
            std::unique_ptr<std::thread> _threading;
    };
}