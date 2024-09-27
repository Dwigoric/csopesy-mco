// ConsoleManager.h : Headers for ConsoleManager class.
#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "AConsole.h"
#include "BaseScreen.h"

const std::string MAIN_CONSOLE = "MAIN_CONSOLE";

class ConsoleManager {
public:
	typedef std::unordered_map<std::string, std::shared_ptr<AConsole>> ConsoleTable;

	static ConsoleManager* getInstance();
	static void initialize();
	static void destroy();

	void drawConsole() const;
	void process() const;
	// void switchConsole() const;

	bool registerScreen(const std::shared_ptr<BaseScreen>& screenRef);
	void switchToScreen(const std::string& name);
	void unregisterScreen(const std::string& name);

	void returnToPreviousConsole();
	void exitApplication();
	bool isRunning() const;

	// HANDLE getConsoleHandle() const;

	// void setCursorPosition(int posX, int posY) const;

	void clearScreen() const;

private:
	ConsoleManager();
	~ConsoleManager() = default;
	ConsoleManager(ConsoleManager const&) {};
	ConsoleManager operator=(ConsoleManager const&) {};

	static ConsoleManager* sharedInstance;

	ConsoleTable consoleTable;
	std::shared_ptr<AConsole> currentConsole;
	std::shared_ptr<AConsole> previousConsole;

	// HANDLE consoleHandle;
	bool running = true;
};

#endif //CONSOLEMANAGER_H
