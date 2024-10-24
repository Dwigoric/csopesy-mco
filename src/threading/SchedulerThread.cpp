#include "SchedulerThread.h"
#include "../console/BaseScreen.h"
#include "../console/ConsoleManager.h"
#include "../util/randint.h"

#include <thread>

SchedulerThread *SchedulerThread::instance = nullptr;

SchedulerThread::SchedulerThread() {
    this->schedulerFCFS = new FCFSScheduler();

    this->currentScheduler = this->schedulerFCFS;
}

void SchedulerThread::startSpawning() {
    //while (this->isSpawning) {
    //    std::shared_ptr<Process> process = std::make_shared<Process>(this->processCounter++,
    //                                                                 std::format("process_{}", this->processCounter));;

    //    this->currentScheduler->scheduleProcess(*process);

    //    // Add delay of 0.5s
    //    sleep(500);
    //}

    for (int i = 0; i < 10; i++) {
        this->createProcess(std::format("screen_{}", this->processCounter));
    }
}

void SchedulerThread::stopSpawning() {
    this->isSpawning = false;
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

bool SchedulerThread::createProcess(std::string name) {
    std::shared_ptr<Process> process = std::make_shared<Process>(this->processCounter, name);
    std::shared_ptr<BaseScreen> screen = std::make_shared<BaseScreen>(process, name);

    if (!ConsoleManager::getInstance()->registerScreen(screen)) {
        // only switch screens if the registration was successful
        return false;
    }

    this->processCounter++;

    int minInstructions = std::stoi(ConsoleManager::getInstance()->getConfigs()["min-ins"]);
    int maxInstructions = std::stoi(ConsoleManager::getInstance()->getConfigs()["max-ins"]);
    int numInstructions = randint(minInstructions, maxInstructions);

    for (int i = 0; i < numInstructions; i++) {
        process->addCommand(AInstruction::PRINT);
    }

    this->registerProcess(process);
    this->currentScheduler->scheduleProcess(process);

    return true;
}

void SchedulerThread::registerProcess(std::shared_ptr<Process> process) {
    this->processes.push_back(process);
}

std::vector<std::shared_ptr<Process>> SchedulerThread::getProcessList() {
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
