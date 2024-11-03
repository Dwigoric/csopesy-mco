#include "InitializeCommand.h"
#include "../console/ConsoleManager.h"
#include "../cpu/CPUManager.h"
#include "../threading/SchedulerThread.h"
#include "../cpu/CPUWorker.h"

#include <iostream>

void InitializeCommand::execute()
{
	ConsoleManager::getInstance()->loadConfigs();
	auto configs = ConsoleManager::getInstance()->getConfigs();

	CPUWorker::delayPerExec = std::stoi(configs.at("delay-per-exec"));
	CPUManager::initialize(std::stoi(configs.at("num-cpu")));
	CPUManager::getInstance()->startAllCores();

	SchedulerThread::initialize(configs.at("scheduler"), std::stoi(configs.at("quantum-cycles")));
	SchedulerThread::getInstance()->start();

	ConsoleManager::getInstance()->setConfigInitialized();
	
	// DEBUG: display current configs
	ConsoleManager::getInstance()->test_printConfigs();
}
