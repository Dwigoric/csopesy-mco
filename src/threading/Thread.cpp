#include "Thread.h"

#include <thread>

void Thread::start() {
	this->thread = std::thread(&Thread::run, this);
}

void Thread::join() {
	this->thread.join();
}

void Thread::sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Thread::~Thread() {
	this->join();
}