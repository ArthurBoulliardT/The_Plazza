/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** plazza
*/

#include "Receptionist.hpp"
#include "Error.hpp"

bool isNumber(const std::string &s)
{
    return  !s.empty() && std::find_if(s.begin(), s.end(),
            [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void launchPlazza(char **argv)
{
    try {
        std::string mult(argv[1]);
        std::string cookNumber(argv[2]);
        std::string refreshTime(argv[3]);
        plzz::Receptionist reception(atof(mult.c_str()), atoi(cookNumber.c_str()), atoi(refreshTime.c_str()));
        logs::Logs log(LOGS_FILE);

        log.file("------------Build new logs------------");
        reception.openRestaurant();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        throw ExecutionError("Stoping the programe");
    }
}
