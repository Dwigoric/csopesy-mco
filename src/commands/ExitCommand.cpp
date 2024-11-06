#include "ExitCommand.h"
#include "../console/ConsoleManager.h"
#include "../cpu/CPUManager.h"
#include "../threading/SchedulerThread.h"
#include "../memory/MemoryManager.h"

void ExitCommand::execute()
{
	ConsoleManager::getInstance()->exitApplication();

	if (ConsoleManager::getInstance()->getConfigInitialized()) {
		SchedulerThread::getInstance()->stopScheduler();
		SchedulerThread::destroy();
		MemoryManager::destroy();
		CPUManager::destroy();
	}
}


