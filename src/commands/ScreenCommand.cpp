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
    int max_cpu = std::stoi(ConsoleManager::getInstance()->getConfigs()["num-cpu"]);
    int used_cpu = 0;

    for (std::shared_ptr<Process> process : SchedulerThread::getInstance()->getProcessList()) {
        if (process->getState() == Process::RUNNING) {
            used_cpu++;
        }
    }

    float utilization = (float)used_cpu / (float)max_cpu;

    std::cout << "CPU Utilization: " << utilization * 100 << "%\n";
    std::cout << "Cores used: " << used_cpu << "\n";
    std::cout << "Cores available: " << max_cpu - used_cpu << "\n\n";
        
    std::cout << "---------------------------------------------\n";
    std::cout << "Running processes:\n";
    for (std::shared_ptr<Process> process: SchedulerThread::getInstance()->getProcessList()) {
        if (process->getState() == Process::RUNNING) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(process->getTimeExecuted());
            std::cout << process->getName() << "   " << std::put_time(std::localtime(&timeCreated_time_t), "(%m/%d/%Y %I:%M:%S%p)") << "   Core: " << process->getCore() << "    " <<
                process->getCurrentInstructionLine() << " / " << process->getMaxInstructionLine() << "\n";
        }
    }

    std::cout << "\nFinished processes:\n";
    for (std::shared_ptr<Process> process: SchedulerThread::getInstance()->getProcessList()) {
        if (process->getState() == Process::FINISHED) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(process->getTimeExecuted());
            std::cout << process->getName() << "   " << std::put_time(std::localtime(&timeCreated_time_t), "(%m/%d/%Y %I:%M:%S%p)") << "   Finished   " <<
                process->getCurrentInstructionLine() << " / " << process->getMaxInstructionLine() << "\n";
        }
    }

    std::cout << "---------------------------------------------\n";
}

