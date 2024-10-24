#include "ExitCommand.h"
#include "../console/ConsoleManager.h"
#include "../cpu/CPUManager.h"
#include "../threading/SchedulerThread.h"

void ExitCommand::execute()
{
	ConsoleManager::getInstance()->exitApplication();

	if (ConsoleManager::getInstance()->getConfigInitialized()) {
		SchedulerThread::getInstance()->stopScheduler();
		SchedulerThread::destroy();
		CPUManager::destroy();
	}
}


