#include "InitializeCommand.h"
#include "../console/ConsoleManager.h"
#include "../cpu/CPUManager.h"
#include "../threading/SchedulerThread.h"
#include "../cpu/CPUWorker.h"
#include "../memory/MemoryManager.h"
#include "../disk/BackingStore.h"

#include <iostream>

void InitializeCommand::execute()
{
	ConsoleManager::getInstance()->loadConfigs();
	auto configs = ConsoleManager::getInstance()->getConfigs();

	MemoryManager::initialize();

	Process::minMemPerProc = std::stoi(configs.at("min-mem-per-proc"));
	Process::maxMemPerProc = std::stoi(configs.at("max-mem-per-proc"));

	CPUWorker::delayPerExec = std::stoi(configs.at("delay-per-exec"));
	CPUManager::initialize(std::stoi(configs.at("num-cpu")));
	CPUManager::getInstance()->startAllCores();

	SchedulerThread::initialize(configs.at("scheduler"), std::stoi(configs.at("quantum-cycles")), MemoryManager::getInstance()->getAllocator());
	SchedulerThread::getInstance()->start();

	BackingStore::initialize();

	ConsoleManager::getInstance()->setConfigInitialized();
	
	// DEBUG: display current configs
	ConsoleManager::getInstance()->test_printConfigs();
}
