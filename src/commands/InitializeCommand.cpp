#include "InitializeCommand.h"
#include "../console/ConsoleManager.h"
#include "../cpu/CPUManager.h"
#include "../threading/SchedulerThread.h"

#include <iostream>

void InitializeCommand::execute()
{
	ConsoleManager::getInstance()->loadConfigs();

	CPUManager::initialize(std::stoi(ConsoleManager::getInstance()->getConfigs().at("num-cpu")));
	CPUManager::getInstance()->startAllCores();

	SchedulerThread::initialize();
	SchedulerThread::getInstance()->start();

	ConsoleManager::getInstance()->setConfigInitialized();
}
