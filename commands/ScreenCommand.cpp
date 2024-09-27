#include <iostream>

#include "ScreenCommand.h"
#include "../console/ConsoleManager.h"

void ScreenCommand::execute(std::vector<std::string> parameters) {
    if (parameters.size() == 0) {
        std::cout << "screen: missing argument\n";
        std::cout << "screen: use -ls to list screens\n";
        std::cout << "screen: use -r <screen name> to switch to a screen\n";
        std::cout << "screen: use -s <screen name> to create a screen\n";
    }
    else {
        if (parameters[0] == "-ls") {
            // TODO: Get list of processes
            // displayProcesses();
        }
        else if (parameters[0] == "-r") {
            if (parameters.size() == 1) {
                std::cout << "screen switch: missing argument (screen name). Use -ls to list screens.\n";
            }
            else {
                ConsoleManager::getInstance()->switchToScreen(parameters[1]);
            }
        }
        else if (parameters[0] == "-s") {
            if (parameters.size() == 1) {
                std::cout << "screen create: missing argument (screen name). Use `screen -s <screen name>` to create a screen.\n";
            }
            else {
                // Create a new screen
            }
        }
        else {
            std::cout << "screen: invalid argument\n";
        }
    }
}

void ScreenCommand::displayProcesses(std::vector<Process> processes) {
    for (Process& process: processes) {
        std::cout << "Name: " << process.getName() << " | Core: " << process.getCore() << " | " <<
            process.getCurrentInstructionLine() << " / " << process.getMaxInstructionLine() << " |\n";
    }
}
