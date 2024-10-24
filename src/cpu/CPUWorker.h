#ifndef CPUWORKER_H
#define CPUWORKER_H

#include "../threading/Thread.h"
#include "../process/Process.h"
#include "../console/ConsoleManager.h"
#include <mutex>

class CPUWorker : public Thread {
public:
    void assignProcess(std::shared_ptr<Process> queuedProcess);
    std::shared_ptr<Process> getProcess() const;

    void start() override;
    void stop();

    std::mutex mutex;
    static int delayPerExec;

private:
    void run() override;

    std::shared_ptr<Process> runningProcess = nullptr;
    bool isRunning = false;
    int cycles = 0;
};

#endif //CPUWORKER_H