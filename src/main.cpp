/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <regex>
#include "Logs.hpp"
#include "plazza.hpp"
#include "Error.hpp"

static int printHelper(void)
{
    logs::Logs log(LOGS_FILE);

    log.output("USAGE:  ./plazza [MULT NB REFRESH] | --help");
    log.output("\tMULT: the coocking time multiplier");
    log.output("\tNB: the number of cooks per kitchens");
    log.output("\tREFRESH: the time of milliseconds for ingredient restock");
    return 0;
}

static void checkMultiplier(char *str)
{
    std::regex floats("(\\w+([.]\\w+)?)");
    std::string subject(str);
    std::string result;
    std::smatch match;

    if (std::regex_search(subject, match, floats) && match.size() > 1) {
        result = match.str(1);
        if (result.size() != subject.size()) {
            throw KitchenError("Wrong multiplier number format");
        }
    }
    else {
        throw KitchenError("Wrong mulitplier number format");
    }
}

static void checkCooksNumber(char *str)
{
    std::string subject(str);

    if (isNumber(subject) == false) {
        throw KitchenError("Wrong number of cooks per kitchens");
    }
}

static void checkRefreshValue(char *str)
{
    std::string subject(str);

    if (isNumber(subject) == false) {
        throw KitchenError("Wrong number for ingredient restock");
    }
}

static void checkErrors(int argc, char **argv)
{
    try {
        if (argc == 4) {
            checkMultiplier(argv[1]);
            checkCooksNumber(argv[2]);
            checkRefreshValue(argv[3]);
        }
        else if (argc == 2) {
            printHelper();
        }
        else {
            throw ExecutionError("Not enough parameters, run --help");
        }
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        throw ExecutionError("Stoping the program");
    }
}

int main(int argc, char **argv)
{
    try {
        checkErrors(argc, argv);
        launchPlazza(argv);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}