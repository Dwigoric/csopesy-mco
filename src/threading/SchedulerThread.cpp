#include "SchedulerThread.h"
#include "../console/BaseScreen.h"
#include "../console/ConsoleManager.h"
#include "../util/randint.h"

SchedulerThread *SchedulerThread::instance = nullptr;

SchedulerThread::SchedulerThread() {
    this->schedulerFCFS = new FCFSScheduler();

    this->currentScheduler = this->schedulerFCFS;
}

void SchedulerThread::startSpawning() {
    this->spawnerThread = new CustomThread([this]() {
        while (this->isSpawning) {
            this->createProcess(std::format("screen_{}", this->processCounter));
        }
    });

    this->isSpawning = true;
    this->spawnerThread->start();
}

void SchedulerThread::stopSpawning() {
    this->isSpawning = false;
    this->spawnerThread->join();
    this->spawnerThread = nullptr;
}

void SchedulerThread::stopScheduler() const {
    this->currentScheduler->stop();
}

void SchedulerThread::switchScheduler(const std::string &scheduler) {
    this->currentScheduler->stop();

    if (scheduler == "FCFS") {
        this->currentScheduler = this->schedulerFCFS;
    }
    // Add more schedulers here
    else {
        throw std::runtime_error("Invalid scheduler");
    }

    this->currentScheduler->run();
}

void SchedulerThread::run() {
    if (this->currentScheduler == nullptr) {
        throw std::runtime_error("Invalid scheduler");
    }

    // this->startSpawning();
    this->currentScheduler->run();
}

bool SchedulerThread::createProcess(const std::string &name) {
    auto process = std::make_shared<Process>(this->processCounter, name);
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
        process->addCommand(AInstruction::PRINT);
    }

    this->registerProcess(process);
    this->currentScheduler->scheduleProcess(process);

    return true;
}

void SchedulerThread::registerProcess(const std::shared_ptr<Process> &process) {
    this->processes.push_back(process);
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

void SchedulerThread::initialize() {
    if (instance == nullptr) {
        instance = new SchedulerThread();
    }
}
