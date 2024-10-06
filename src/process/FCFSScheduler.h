#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H


#include "AScheduler.h"

class FCFSScheduler : public AScheduler {
public:
    FCFSScheduler();

    void init() override;

    void execute() override;
};


#endif //FCFSSCHEDULER_H
