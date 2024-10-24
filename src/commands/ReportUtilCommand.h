#pragma once

#include "ACommand.h"

#include "../process/Process.h"
#include "../console/ConsoleManager.h"
#include "../threading/SchedulerThread.h"

#include <chrono>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

class ReportUtilCommand : public ACommand {
public:
    static void execute();
    static void printProcesses(std::ostream& os);
};