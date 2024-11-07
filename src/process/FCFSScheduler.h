#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H


#include "AScheduler.h"

class FCFSScheduler : public AScheduler {
public:
    FCFSScheduler(std::shared_ptr<IMemoryAllocator> memoryAllocator);

    void init() override;

    void execute() override;
};


#endif //FCFSSCHEDULER_H
