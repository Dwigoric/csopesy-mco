#include "InitializeCommand.h"
#include "../console/ConsoleManager.h"
#include "../cpu/CPUManager.h"
#include "../threading/SchedulerThread.h"
#include "../cpu/CPUWorker.h"
#include "../memory/MemoryManager.h"

#include <iostream>

void InitializeCommand::execute()
{
	ConsoleManager::getInstance()->loadConfigs();
	auto configs = ConsoleManager::getInstance()->getConfigs();

	MemoryManager::initialize();

	Process::memPerProc = std::stoi(configs.at("mem-per-proc"));

	CPUWorker::delayPerExec = std::stoi(configs.at("delay-per-exec"));
	CPUManager::initialize(std::stoi(configs.at("num-cpu")));
	CPUManager::getInstance()->startAllCores();

	SchedulerThread::initialize(configs.at("scheduler"), std::stoi(configs.at("quantum-cycles")));
	SchedulerThread::getInstance()->start();


	ConsoleManager::getInstance()->setConfigInitialized();
	
	// DEBUG: display current configs
	ConsoleManager::getInstance()->test_printConfigs();
}
