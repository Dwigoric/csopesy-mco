#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H


#include <functional>

#include "Thread.h"

class CustomThread : public Thread {
public:
    explicit CustomThread(const std::function<void()> &function);

    void run() override;

private:
    std::function<void()> function;
};


#endif //CUSTOMTHREAD_H
