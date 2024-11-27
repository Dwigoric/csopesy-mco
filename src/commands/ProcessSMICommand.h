#pragma once

#include "ACommand.h"

#include <iostream>

#include "../console/ConsoleManager.h"
#include "../process/Process.h"
#include "../threading/SchedulerThread.h"
#include "../cpu/CPUManager.h"

class ProcessSMICommand : ACommand {
public:
    static void execute();
};