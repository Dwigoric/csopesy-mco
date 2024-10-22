#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
public:
	virtual ~Thread();

	virtual void start();

	void join();

	static void sleep(int ms);

protected:
	std::thread thread;

	virtual void run() = 0;
};


#endif //THREAD_H
