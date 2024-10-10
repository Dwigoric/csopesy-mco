// ConsoleManager.h : Headers for ConsoleManager class.
#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <memory>
#include <unordered_map>

#include "AConsole.h"
#include "BaseScreen.h"

const std::string MAIN_CONSOLE = "MAIN_CONSOLE";

class ConsoleManager {
public:
	typedef std::unordered_map<std::string, std::shared_ptr<AConsole> > ConsoleTable;
	typedef std::unordered_map<std::string, std::string> ConfigTable;

	static ConsoleManager *getInstance();

	static void initialize();

	static void destroy();

	void drawConsole() const;

	void process() const;

	// void switchConsole() const;

	bool registerScreen(const std::shared_ptr<BaseScreen> &screenRef);

	void switchToScreen(const std::string &name);

	void unregisterScreen(const std::string &name);

	void returnToPreviousConsole();

	void exitApplication();

	bool isRunning() const;

	// HANDLE getConsoleHandle() const;

	// void setCursorPosition(int posX, int posY) const;

	void clearScreen() const;

	void loadConfigs();

	ConfigTable getConfigs();

	// TEMP: For Homework 6 Only
	void test_create10PrintProcesses();

private:
	ConsoleManager();

	~ConsoleManager() = default;

	ConsoleManager(ConsoleManager const &) {
	};

	ConsoleManager operator=(ConsoleManager const &);

	static ConsoleManager *sharedInstance;

	ConsoleTable consoleTable;
	std::shared_ptr<AConsole> currentConsole;
	std::shared_ptr<AConsole> previousConsole;

	// HANDLE consoleHandle;
	bool running = true;

	ConfigTable configs;
	const ConfigTable defaultConfigs = {
		std::make_pair<>("num-cpu", "4")
	};
};

#endif //CONSOLEMANAGER_H
