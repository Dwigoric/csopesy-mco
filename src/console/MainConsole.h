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
	static void clear();

	static void initialize();

	static void report_util();

	std::vector<Process> processes;
};

#endif //MAINCONSOLE_H
