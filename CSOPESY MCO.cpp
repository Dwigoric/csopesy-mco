// CSOPESY MCO.cpp : Defines the entry point for the application.
//

#include "CSOPESY MCO.h"

int main() {
	ConsoleManager::initialize();

	printHeader();

	bool terminate = false;
	std::string command;

	do {
		printCommandPrefix();

		std::cin >> command;

		if (command == "exit") terminate = true;
		else if (command == "clear") clear();
		else if (command == "initialize") initialize();
		else if (command == "screen") screen();
		else if (command == "scheduler-test") scheduler_test();
		else if (command == "scheduler-stop") scheduler_stop();
		else if (command == "report-util") report_util();
		else {
			std::cout << "Commands list:" << std::endl;
			std::cout << "exit - exit the program" << std::endl;
			std::cout << "clear - clear the screen" << std::endl;
			std::cout << "initialize - initialize the program" << std::endl;
			std::cout << "screen - display the screen" << std::endl;
			std::cout << "scheduler-test - test the scheduler" << std::endl;
			std::cout << "scheduler-stop - stop the scheduler" << std::endl;
			std::cout << "report-util - display the report utility" << std::endl;
		}
	} while (!terminate);

	ConsoleManager::destroy();

	return 0;
}

// Command functions
void initialize() {
	std::cout << "`initialize` command recognized. Doing something." << std::endl;
}

void screen() {
	std::cout << "`screen` command recognized. Doing something." << std::endl;
}

void scheduler_test() {
	std::cout << "`scheduler-test` command recognized. Doing something." << std::endl;
}

void scheduler_stop() {
	std::cout << "`scheduler-stop` command recognized. Doing something." << std::endl;
}

void report_util() {
	std::cout << "`report-util` command recognized. Doing something." << std::endl;
}

// Basic display functions
void printHeader() {
	std::cout << "a88888b. .d88888b   .88888.   888888ba   88888888b .d88888b  dP    dP" << std::endl;
	std::cout << "d8'   `88 88.    \"' d8'   `8b  88    `8b  88        88.    \"' Y8.  .8P" << std::endl;
	std::cout << "88        `Y88888b. 88     88 a88aaaa8P' a88aaaa    `Y88888b.  Y8aa8P" << std::endl;
	std::cout << "88              `8b 88     88  88         88              `8b    88" << std::endl;
	std::cout << "Y8.   .88 d8'   .8P Y8.   .8P  88         88        d8'   .8P    88" << std::endl;
	std::cout << "Y88888P'  Y88888P   `8888P'   dP         88888888P  Y88888P     dP" << std::endl;
	std::cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << std::endl;
	std::cout << std::endl;
	std::cout << "Hello! Welcome to the CSOPESY command line." << std::endl;
	std::cout << "Type 'exit' to exit, 'clear' to clear the screen" << std::endl;
}

void printCommandPrefix() {
	std::cout << "user@CSOPESY:~$ ";
}

void clear() {
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	// system("clear");
	std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
	system("clear");
#endif

	printHeader();
}
