// ConsoleManager.cpp : Console Manager singleton class for displaying and transitioning
//						between screens.

#include "ConsoleManager.h"
#include "MainConsole.h"

#include "../util/string-tokenizer.h"

#include <fstream>

typedef std::unordered_map < std::string, std::string > ConfigTable;

ConsoleManager *ConsoleManager::sharedInstance = nullptr;

ConsoleManager *ConsoleManager::getInstance() {
	return sharedInstance;
}

// static
void ConsoleManager::initialize() {
	sharedInstance = new ConsoleManager();
}

// static
void ConsoleManager::destroy() {
	if (sharedInstance != nullptr) {
		delete sharedInstance;
	}
}

// drawConsole() : Call every frame to display the current console screen.
void ConsoleManager::drawConsole() const {
	if (this->currentConsole == nullptr) {
		std::cerr << "Attempted to draw current console, but current console is null\n";

		return;
	}

	this->currentConsole->display();
}

// process() : Call every time console logic needs to be processed.
void ConsoleManager::process() const {
	if (this->currentConsole == nullptr) {
		std::cerr << "Attempted to process current console, but current console is null\n";

		return;
	}

	this->currentConsole->process();
}

// This function is exactly the same as switchToScreen, so it's not being implemented
/* void ConsoleManager::switchConsole() const
{
} */

// registerScreen() : Add a BaseScreen to the Console manager's list of registered screens
//					  to display.
// 
bool ConsoleManager::registerScreen(const std::shared_ptr<BaseScreen> &screenRef) {
	std::string name = screenRef->getName();

	if (consoleTable.contains(name)) {
		std::cerr << "Error: Attempted to create screen with name "
				<< name
				<< ", but a screen with that name already exists\n";

		return false;
	}

	this->consoleTable.insert(std::make_pair(name, screenRef));

	return true;
}

// switchToScreen() : Switch the current screen to another registered screen defined by the
//					  screen name.
void ConsoleManager::switchToScreen(const std::string &name) {
	if (!consoleTable.contains(name)) {
		std::cerr << "Process " << name << " not found.\n";

		return;
	}

	this->clearScreen();

	this->previousConsole = this->currentConsole;
	this->currentConsole = this->consoleTable.at(name);
	this->currentConsole->onEnabled();
}

// unregisterScreen() : Remove a screen with the given name from the screens table. 
//						Note: If the screen being removed is currently being displayed, 
//                      the screen will still be available to display until the screen is
//						switched out.
void ConsoleManager::unregisterScreen(const std::string &name) {
	if (!consoleTable.contains(name)) {
		std::cerr << "Error: Attempted to unregister screen "
				<< name
				<< ", but no screen with that name was found\n";

		return;
	}

	this->consoleTable.erase(name);
}

// returnToPreviousConsole : Switches screen to the previously accessed screen.
void ConsoleManager::returnToPreviousConsole() {
	if (this->previousConsole == nullptr) {
		std::cerr << "Error: Attempted to return to previous console, but previous console was null\n";

		return;
	}

	this->clearScreen();

	this->currentConsole = this->previousConsole;
	this->previousConsole = nullptr;
	this->currentConsole->onEnabled();
}

void ConsoleManager::exitApplication() {
	this->running = false;
}

bool ConsoleManager::isRunning() const {
	return this->running;
}

/*
HANDLE ConsoleManager::getConsoleHandle() const
{
	return consoleHandle;
}
*/

/*
void ConsoleManager::setCursorPosition(int posX, int posY) const
{

}
*/

ConsoleManager::ConsoleManager() {
	// TEMP: not using Windows.h console handles yet
	// consoleHandle = nullptr;

	this->currentConsole = nullptr;
	this->previousConsole = nullptr;

	const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();

	this->consoleTable[MAIN_CONSOLE] = mainConsole;

	this->switchToScreen(MAIN_CONSOLE);
}

// clearScreen() : Platform-wide utility function for clearing screens
void ConsoleManager::clearScreen() const {
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	// system("clear");
	std::cout << u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
	system("clear");
#endif
}

void ConsoleManager::loadConfigs()
{
	this->configs = {};

	std::ifstream fs("config.txt");
	std::string line;
	std::vector<std::string> tokens;

	// get all user-defined configs
	while (fs.peek() != EOF) {
		std::getline(fs, line);
		tokens = tokenize(line);

		if (tokens[1].starts_with('"')) {
			tokens[1] = tokens[1].substr(1, tokens[1].length() - 2);
		}

		this->configs.insert(std::make_pair<>(tokens[0], tokens[1]));
	}

	// fill up the rest with default configs
	for (auto it = this->defaultConfigs.begin(); it != this->defaultConfigs.end(); it++) {
		if (!this->configs.contains(it->first)) {
			this->configs.insert(std::make_pair<>(it->first, it->second));
		}
	}

	fs.close();
}

ConfigTable ConsoleManager::getConfigs()
{
	return configs;
}

void ConsoleManager::test_printConfigs() {
	for (auto it = this->configs.begin(); it != this->configs.end(); it++) {
		std::cout << it->first << ": " << it->second << "\n";
	}
}

void ConsoleManager::setConfigInitialized()
{
	this->configInitialized = true;
}

bool ConsoleManager::getConfigInitialized()
{
	return this->configInitialized;
}

ConsoleManager ConsoleManager::operator=(ConsoleManager const &) {
	return *this;
}
