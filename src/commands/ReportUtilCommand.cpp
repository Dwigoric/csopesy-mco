#include "ReportUtilCommand.h"
#include "../cpu/CPUManager.h"

void ReportUtilCommand::execute()
{
    std::ofstream fs("csopesy-log.txt");
    printProcesses(fs);
    fs.close();

    std::filesystem::path filepath = std::filesystem::current_path();
    filepath /= "csopesy-log.txt";
    std::cout << "Report generated at " << filepath << "\n";
}

void ReportUtilCommand::printProcesses(std::ostream& os)
{
    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.lock();
    }

    int max_cpu = std::stoi(ConsoleManager::getInstance()->getConfigs()["num-cpu"]);
    int used_cpu = 0;

    for (auto core : CPUManager::getInstance()->getCores()) {
        auto p = core->getProcess();
        if (p) {
            used_cpu++;
        }
    }

    float utilization = (float)used_cpu / (float)max_cpu;   

    os << "CPU Utilization: " << utilization * 100 << "%\n";
    os << "Cores used: " << used_cpu << "\n";
    os << "Cores available: " << max_cpu - used_cpu << "\n\n";

    os << "---------------------------------------------\n";
    os << "Running processes:\n";
    for (auto core : CPUManager::getInstance()->getCores()) {
        auto p = core->getProcess();
        if (p) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(p->getTimeExecuted());
            os << p->getName() << "   " << std::put_time(std::localtime(&timeCreated_time_t), "(%m/%d/%Y %I:%M:%S%p)") << "   Core: " << p->getCore() << "    " <<
                p->getCurrentInstructionLine() << " / " << p->getMaxInstructionLine() << "\n";
        }
    }

    os << "\nFinished processes:\n";
    for (std::shared_ptr<Process> process : SchedulerThread::getInstance()->getProcessList()) {
        if (process->getState() == Process::FINISHED) {
            auto timeCreated_time_t = std::chrono::system_clock::to_time_t(process->getTimeExecuted());
            os << process->getName() << "   " << std::put_time(std::localtime(&timeCreated_time_t), "(%m/%d/%Y %I:%M:%S%p)") << "   Finished   " <<
                process->getCurrentInstructionLine() << " / " << process->getMaxInstructionLine() << "\n";
        }
    }

    os << "---------------------------------------------\n";

    for (CPUWorker* core : CPUManager::getInstance()->getCores()) {
        core->mutex.unlock();
    }
}
