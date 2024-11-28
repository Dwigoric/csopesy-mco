#ifndef CPUMANAGER_H
#define CPUMANAGER_H

#include <vector>
#include "CPUWorker.h"

class CPUManager {
public:
	static CPUManager* getInstance();
	static void initialize(int numCores);
	static void destroy();

	std::vector<CPUWorker*> getCores();
	void startAllCores();
	void stopAllCores();

	size_t getActiveCycles();
	size_t getInactiveCycles();

private:
	CPUManager(int numCores);
	~CPUManager();
	CPUManager(CPUManager const&) = delete;
	CPUManager& operator=(CPUManager const&) = delete;

	static CPUManager* instance;

	std::vector<CPUWorker*> cores;
};

#endif //CPUMANAGER_H