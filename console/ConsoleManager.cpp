#include "ConsoleManager.h"

ConsoleManager* ConsoleManager::sharedInstance = nullptr;

ConsoleManager* ConsoleManager::getInstance()
{
	return sharedInstance;
}

void ConsoleManager::initialize()
{
	sharedInstance = new ConsoleManager();
}

void ConsoleManager::destroy()
{
	delete sharedInstance;
}

void ConsoleManager::drawConsole() const
{
	// TODO
}

void ConsoleManager::process() const
{
	// TODO
}

void ConsoleManager::switchConsole() const
{
	// TODO
}

void ConsoleManager::registerScreen(std::shared_ptr<AConsole> screenRef)
{
	// TODO
}

void ConsoleManager::switchToScreen(std::string name)
{
	// TODO
}

void ConsoleManager::unregisterScreen(std::string name)
{
	// TODO
}

void ConsoleManager::returnToPreviousConsole()
{
	// TODO
}

void ConsoleManager::exitApplication()
{
	// TODO
}

bool ConsoleManager::isRunning() const
{
	return running;
}

HANDLE ConsoleManager::getConsoleHandle() const
{
	return consoleHandle;
}

void ConsoleManager::setCursorPosition(int posX, int posY) const
{

}

ConsoleManager::ConsoleManager()
{
	// TEMP: not using Windows.h console handles yet
	consoleHandle = nullptr;
}
