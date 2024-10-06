#include "AScheduler.h"

AScheduler::AScheduler(SchedulingAlgorithm algorithm) {
    this->algorithm = algorithm;
}

void AScheduler::run() {
    this->running = true;
    init();
    while (this->running) {
        execute();
    }
}

void AScheduler::stop() {
    this->running = false;
}


