#ifndef MAINCONSOLE_H
#define MAINCONSOLE_H

#include "AConsole.h"
#include "../process/Process.h"
#include <vector>

constexpr int DUMMY_PROCESS_COUNT = 50;


class MainConsole : public AConsole {
public:
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	// Printer functions
	static void printHeader();
	static void printCommandPrefix();

	// Command functions
	void clear();
	void initialize();
	void screen();
	void scheduler_test();
	void scheduler_stop();
	void report_util();
	void display_processes();

	std::vector<Process> processes;
};

#endif //MAINCONSOLE_H
