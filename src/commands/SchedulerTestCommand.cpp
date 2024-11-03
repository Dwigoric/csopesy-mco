#include "SchedulerTestCommand.h"

#include "../threading/SchedulerThread.h"

void SchedulerTestCommand::execute() {
	SchedulerThread::getInstance()->startSpawning();
}
