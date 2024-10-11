#include "SchedulerStopCommand.h"

#include "../threading/SchedulerThread.h"

void SchedulerStopCommand::execute() {
    SchedulerThread::getInstance()->stopSpawning();
    SchedulerThread::getInstance()->stopScheduler();
}

