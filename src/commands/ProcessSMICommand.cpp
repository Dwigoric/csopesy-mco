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

    size_t totalMemory = MemoryManager::getInstance()->getTotalMemory();

    auto processMemoryUsage = MemoryManager::getInstance()->getProcessMemoryUsage();
    int totalMemoryUsage = 0;

    for (auto core : CPUManager::getInstance()->getCores()) {
        auto p = core->getProcess();
        if (p) {
            used_cpu++;
            if (processMemoryUsage.contains(p->getId())) {
                totalMemoryUsage += processMemoryUsage.at(p->getId());
            }
        }
    }

    float utilization = (float)used_cpu / (float)max_cpu;

    std::cout << "CPU-Util: " << utilization * 100 << "%\n";
    std::cout << "Memory Usage: " << totalMemoryUsage << "KB / " << totalMemory << "KB\n";
    std::cout << "Memory Util: " << (totalMemoryUsage * 100) / (totalMemory * 100) << "%\n\n";

    std::cout << "---------------------------------------------\n";
    std::cout << "Running processes and memory usage: \n";
    std::cout << "---------------------------------------------\n";

    for (auto core : CPUManager::getInstance()->getCores()) {
        auto p = core->getProcess();
        if (p) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(p->getTimeExecuted());
            int memoryUsage = processMemoryUsage.contains(p->getId())
                ? processMemoryUsage.at(p->getId())
                : 0;
        
            std::cout << p->getName() << " " << memoryUsage << "KB\n";
        }
    }

    std::cout << "---------------------------------------------\n";

    // DEBUG: show whole memory map
    // MemoryManager::getInstance()->printDetails(std::cout);

    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.unlock();
    }
}
