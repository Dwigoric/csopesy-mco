#pragma once

#include "ACommand.h"

#include <iostream>
#include <map>

#include "../console/ConsoleManager.h"
#include "../process/Process.h"
#include "../threading/SchedulerThread.h"
#include "../cpu/CPUManager.h"
#include "../memory/MemoryManager.h"
#include "../disk/BackingStore.h"

class VMStatCommand : ACommand {
public:
    static void execute();
private:
    static void printStat(std::string label, int value);
};