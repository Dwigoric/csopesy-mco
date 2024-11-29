#include "VMStatCommand.h"

void VMStatCommand::execute()
{
    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.lock();
    }

    size_t totalMemory = MemoryManager::getInstance()->getTotalMemory();

    auto processMemoryUsage = MemoryManager::getInstance()->getProcessMemoryUsage();
    int totalMemoryUsage = 0;

    for (auto entry : processMemoryUsage) {
        totalMemoryUsage += entry.second;
    }

    // total memory in KB
    printStat("KB Total Memory", totalMemory);

    // total active memory used by processes in KB
    printStat("KB Used Memory", totalMemoryUsage);

    // total free memory that can still be used by other processes in KB
    printStat("KB Free Memory", totalMemory - totalMemoryUsage);

	// idle cpu ticks
    size_t activeCycles = CPUManager::getInstance()->getActiveCycles();
    size_t inactiveCycles = CPUManager::getInstance()->getInactiveCycles();

    printStat("Idle CPU Ticks", inactiveCycles);

	// active cpu ticks
    printStat("Active CPU Ticks", activeCycles);

	// total cpu ticks
    printStat("Total CPU Ticks", activeCycles + inactiveCycles);

	// num paged in
    printStat("Num paged in", BackingStore::getInstance()->getNumPagedIn());

	// num paged out
    printStat("Num paged out", BackingStore::getInstance()->getNumPagedOut());

    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.unlock();
    }
}

void VMStatCommand::printStat(std::string label, int value)
{
    printf("%14d %s\n", value, label.c_str());
}

