#include "CPUManager.h"
#include <mutex>
#include <chrono>

CPUManager* CPUManager::instance = nullptr;

CPUManager::CPUManager(int numCores) {
	if (this->cores.empty()) {
		for (int i = 0; i < numCores; i++) {
			this->cores.push_back(new CPUWorker());
		}
	}
}

void CPUManager::initialize(int numCores) {
	instance = new CPUManager(numCores);
}

CPUManager::~CPUManager() {
	//this->stopAllCores();
	CPUWorker* temp;
	for (auto it = this->cores.begin(); it != this->cores.end(); it++) {
		temp = *it;
		std::unique_lock<std::mutex> lock(temp->mutex);
		temp->stop();
		lock.unlock();
		delete temp;
	}
	this->cores.clear();
}

void CPUManager::destroy() {
	delete instance;
}

CPUManager* CPUManager::getInstance() {
	return instance;
}

std::vector<CPUWorker*> CPUManager::getCores() {
	return this->cores;
}

void CPUManager::startAllCores() {
	for (auto it = this->cores.begin(); it != this->cores.end(); it++) {
		(*it)->start();
	}
}

void CPUManager::stopAllCores() {
	for (auto it = this->cores.begin(); it != this->cores.end(); it++) {
		(*it)->stop();
	}
}

size_t CPUManager::getActiveCycles() {
	size_t activeCycles = 0;
	
	for (auto core : this->cores) {
		activeCycles += core->getActiveCycles();
	}

	return activeCycles;
}

size_t CPUManager::getInactiveCycles()
{
	size_t inactiveCycles = 0;

	for (auto core : this->cores) {
		inactiveCycles += core->getInactiveCycles();
	}

	return inactiveCycles;
}
