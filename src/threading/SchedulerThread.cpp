#include "SchedulerThread.h"

#include "../console/BaseScreen.h"
#include "../console/ConsoleManager.h"
#include "../memory/MemoryManager.h"
#include "../util/randint.h"
#include "../process/FCFSScheduler.h"
#include "../process/RoundRobinScheduler.h"

SchedulerThread *SchedulerThread::instance = nullptr;

SchedulerThread::SchedulerThread(const std::string &scheduler, const int quantum, std::shared_ptr<IMemoryAllocator> memoryAllocator) {
    if (scheduler == "fcfs") {
        this->currentScheduler = new FCFSScheduler(memoryAllocator);
    } else if (scheduler == "rr") {
        this->currentScheduler = new RoundRobinScheduler(quantum, memoryAllocator);
    }
}

void SchedulerThread::startSpawning() const {
    this->currentScheduler->startSpawning();
}

void SchedulerThread::stopSpawning() const {
    this->currentScheduler->stopSpawning();
}

void SchedulerThread::stopScheduler() const {
    this->currentScheduler->stop();
}

void SchedulerThread::run() {
    if (this->currentScheduler == nullptr) {
        throw std::runtime_error("Invalid scheduler");
    }

    this->currentScheduler->run();
}

size_t generateRandomProcessSize() {
    if (MemoryManager::getInstance()->getAllocatorType() == MemoryManager::PAGING_ALLOCATOR && Process::minMemPerProc >= Process::pageSize) {
        return randint(Process::minMemPerProc / Process::pageSize, Process::maxMemPerProc / Process::pageSize) * Process::pageSize;
    } else {
        return randint(Process::minMemPerProc, Process::maxMemPerProc);
    }
}

bool SchedulerThread::createProcess(const std::string &name) {
    auto process = std::make_shared<Process>(this->processCounter, name, generateRandomProcessSize());
    auto screen = std::make_shared<BaseScreen>(process, name);

    if (!ConsoleManager::getInstance()->registerScreen(screen)) {
        // only switch screens if the registration was successful
        return false;
    }

    this->processCounter++;

    const int minInstructions = std::stoi(ConsoleManager::getInstance()->getConfigs()["min-ins"]);
    const int maxInstructions = std::stoi(ConsoleManager::getInstance()->getConfigs()["max-ins"]);
    const int numInstructions = randint(minInstructions, maxInstructions);

    for (int i = 0; i < numInstructions; i++) {
        process->addCommand(AInstruction::NOOP);
    }

    this->registerProcess(process);
    this->currentScheduler->scheduleProcess(process);

    return true;
}

void SchedulerThread::registerProcess(const std::shared_ptr<Process> &process) {
    this->processes.push_back(process);
}

int SchedulerThread::getProcessCounter() const {
    return this->processCounter;
}

std::vector<std::shared_ptr<Process> > SchedulerThread::getProcessList() {
    return this->processes;
}

SchedulerThread *SchedulerThread::getInstance() {
    return instance;
}

void SchedulerThread::destroy() {
    delete getInstance();
}

void SchedulerThread::initialize(const std::string &scheduler, const int quantum, std::shared_ptr<IMemoryAllocator> memoryAllocator) {
    if (instance == nullptr) {
        instance = new SchedulerThread(scheduler, quantum, memoryAllocator);
    }
}
