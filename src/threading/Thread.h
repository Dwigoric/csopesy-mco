#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
public:
	void start();
	static void sleep(int ms);

protected:
	virtual void run() = 0;
};

#endif //THREAD_H
