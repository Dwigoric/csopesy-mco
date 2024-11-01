// BaseScreen.h : Headers for BaseScreen class.
#ifndef BASESCREEN_H
#define BASESCREEN_H

#include <memory>
#include <string>
#include <iostream>

#include "../process/Process.h"
#include "AConsole.h"

class BaseScreen : public AConsole {
public:
	BaseScreen(const std::shared_ptr<Process>& process, const std::string& processName);
		
	void onEnabled() override;
	void display() override;
	void process() override;

	void printProcessInfo();
	std::shared_ptr<Process> attachedProcess;
	bool refreshed = false;

private:
	static void printCommandPrefix();
};

#endif //BASESCREEN_H
