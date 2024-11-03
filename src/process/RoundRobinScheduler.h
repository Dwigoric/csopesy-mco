#ifndef ROUNDRROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H


#include "AScheduler.h"

class RoundRobinScheduler : public AScheduler {
public:
    RoundRobinScheduler(int quantum);

    void init() override;

    void execute() override;

private:
    int quantum;
};


#endif //ROUNDROBINSCHEDULER_H
