#ifndef SCREENCOMMAND_H
#define SCREENCOMMAND_H

#include <vector>
#include <string>

#include "ACommand.h"

#include "../process/Process.h"
#include "../console/ConsoleManager.h"
#include "../threading/SchedulerThread.h"
#include "ReportUtilCommand.h"

class ScreenCommand : public ACommand {
public:
    static void execute(std::vector<std::string> parameters);


private:
    static void displayProcesses();
};

#endif //SCREENCOMMAND_H
