#ifndef THREAD_H
#define THREAD_H


class Thread {
public:
	virtual ~Thread() = default;

	void start();

	static void sleep(int ms);

protected:
	virtual void run() = 0;
};


#endif //THREAD_H
