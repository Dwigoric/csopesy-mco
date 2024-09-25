#pragma once

#include "AConsole.h"

class MainConsole : public AConsole {
public:
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	// Printer functions
	void printHeader();
	void printCommandPrefix();

	// Command functions
	void clear();
	void initialize();
	void screen();
	void scheduler_test();
	void scheduler_stop();
	void report_util();
};