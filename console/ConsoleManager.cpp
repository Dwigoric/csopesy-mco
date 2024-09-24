// ConsoleManager.cpp : Console Manager singleton class for displaying and transitioning
//						between screens.

#include "ConsoleManager.h"

ConsoleManager* ConsoleManager::sharedInstance = nullptr;

ConsoleManager* ConsoleManager::getInstance()
{
	return sharedInstance;
}

// static
void ConsoleManager::initialize()
{
	sharedInstance = new ConsoleManager();
}

// static
void ConsoleManager::destroy()
{
	delete sharedInstance;
	
}

// drawConsole() : Call every frame to display the current console screen.
void ConsoleManager::drawConsole() const
{
	if (this->currentConsole == nullptr) {
		std::cerr << "Attempted to draw current console, but current console is null"
			<< std::endl;

		return;
	}

	this->currentConsole->display();
}

// process() : Call every time console logic needs to be processed.
void ConsoleManager::process() const
{
	if (this->currentConsole == nullptr) {
		std::cerr << "Attempted to process current console, but current console is null"
			<< std::endl;

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
void ConsoleManager::registerScreen(std::shared_ptr<BaseScreen> screenRef)
{
	this->consoleTable.insert(std::make_pair(screenRef->getName(), screenRef));
}

// switchToScreen() : Switch the current screen to another registered screen defined by the
//					  screen name.
void ConsoleManager::switchToScreen(std::string name)
{
	if (!consoleTable.contains(name)) {
		std::cerr << "Error: Attempted to switch to screen "
			<< name
			<< ", but no screen with that name was found"
			<< std::endl;

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
void ConsoleManager::unregisterScreen(std::string name)
{
	if (!consoleTable.contains(name)) {
		std::cerr << "Error: Attempted to unregister screen "
			<< name
			<< ", but no screen with that name was found"
			<< std::endl;

		return;
	}

	this->consoleTable.erase(name);
}

// returnToPreviousConsole : Switches screen to the previously accessed screen.
void ConsoleManager::returnToPreviousConsole()
{
	if (this->previousConsole == nullptr) {
		std::cerr << "Error: Attempted to return to previous console, but previous console was null"
			<< std::endl;

		return;
	}

	this->clearScreen();

	this->currentConsole = this->previousConsole;
	this->previousConsole = nullptr;
	this->currentConsole->onEnabled();
}

void ConsoleManager::exitApplication()
{
	this->running = false;
}

bool ConsoleManager::isRunning() const
{
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

ConsoleManager::ConsoleManager()
{
	// TEMP: not using Windows.h console handles yet
	// consoleHandle = nullptr;

	this->currentConsole = nullptr;
	this->previousConsole = nullptr;
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