#include <iostream>

#include "ScreenCommand.h"

void ScreenCommand::execute(std::vector<std::string> parameters, std::vector<Process> &processes) {
    if (parameters.size() == 0) {
        std::cout << "screen: missing argument\n";
        std::cout << "screen: use -ls to list screens\n";
        std::cout << "screen: use -r <screen name> to switch to a screen\n";
        std::cout << "screen: use -s <screen name> to create a screen\n";
    } else {
        if (parameters[0] == "-ls") {
            // TODO: Get list of processes
            displayProcesses(processes);
        } else if (parameters[0] == "-r") {
            if (parameters.size() == 1) {
                std::cout << "screen switch: missing argument (screen name). Use -ls to list screens.\n";
            } else {
                ConsoleManager::getInstance()->switchToScreen(parameters[1]);
            }
        } else if (parameters[0] == "-s") {
            if (parameters.size() == 1) {
                std::cout <<
                        "screen create: missing argument (screen name). Use `screen -s <screen name>` to create a screen.\n";
            } else {
                std::shared_ptr<Process> someProcess = std::make_shared<Process>(123123, parameters[1]);
                std::shared_ptr<BaseScreen> newScreen = std::make_shared<BaseScreen>(someProcess, parameters[1]);
                if (ConsoleManager::getInstance()->registerScreen(newScreen)) {
                    // only switch screens if the registration was successful
                    ConsoleManager::getInstance()->switchToScreen(parameters[1]);
                }
            }
        } else {
            std::cout << "screen: invalid argument\n";
        }
    }
}

/*
 * Format: process_name date_stamp, Core, current_instruction / max_instruction
 */

void ScreenCommand::displayProcesses(std::vector<Process>& processes) {
    ReportUtilCommand::printProcesses(std::cout);
}

