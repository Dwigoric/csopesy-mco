#include "CustomThread.h"

CustomThread::CustomThread(const std::function<void()> &function) {
    this->function = function;
}

void CustomThread::run() {
    this->function();
}
