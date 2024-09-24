// BaseScreen.h : Headers for BaseScreen class.

#pragma once
#include <memory>
#include <string>
#include <iostream>

#include "../process/Process.h"
#include "AConsole.h"

class BaseScreen : public AConsole {
public:
	BaseScreen(std::shared_ptr<Process> process, std::string processName);
		
	void onEnabled() override;
	void display() override;
	void process() override;

	void printProcessInfo() const;
	std::shared_ptr<Process> attachedProcess;
	bool refreshed = false;
};