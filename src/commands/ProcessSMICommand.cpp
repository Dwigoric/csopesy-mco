#include "ProcessSMICommand.h"

void ProcessSMICommand::execute()
{
	// header

	std::cout << "--------------------------------------------" << "\n";
	std::cout << "| PROCESS-SMI V1.00 DRIVER VERSION 01.00 |" << "\n";
	std::cout << "--------------------------------------------" << "\n";

    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.lock();
    }

    int max_cpu = std::stoi(ConsoleManager::getInstance()->getConfigs()["num-cpu"]);
    int used_cpu = 0;

    for (auto core : CPUManager::getInstance()->getCores()) {
        auto p = core->getProcess();
        if (p) {
            used_cpu++;
        }
    }

    float utilization = (float)used_cpu / (float)max_cpu;

    std::cout << "CPU Utilization: " << utilization * 100 << "%\n";

    std::cout << "---------------------------------------------\n";
    std::cout << "Running processes:\n";
    for (auto core : CPUManager::getInstance()->getCores()) {
        auto p = core->getProcess();
        if (p) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(p->getTimeExecuted());
            std::cout << p->getName() << "   " << std::put_time(std::localtime(&timeCreated_time_t), "(%m/%d/%Y %I:%M:%S%p)") << "   Core: " << p->getCore() << "    " <<
                p->getCurrentInstructionLine() << " / " << p->getMaxInstructionLine() << "\n";
        }
    }

    std::cout << "\nFinished processes:\n";
    for (std::shared_ptr<Process> process : SchedulerThread::getInstance()->getProcessList()) {
        if (process->getState() == Process::FINISHED) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(process->getTimeExecuted());
            std::cout << process->getName() << "   " << std::put_time(std::localtime(&timeCreated_time_t), "(%m/%d/%Y %I:%M:%S%p)") << "   Finished   " <<
                process->getCurrentInstructionLine() << " / " << process->getMaxInstructionLine() << "\n";
        }
    }

    std::cout << "---------------------------------------------\n";

    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.unlock();
    }
}
