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

	void test_printConfigs();

	void setConfigInitialized();
	bool getConfigInitialized();
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
	bool configInitialized = false;

	ConfigTable configs;
	const ConfigTable defaultConfigs = {
		std::make_pair<>("num-cpu", "4"),
		std::make_pair<>("scheduler", "rr"),
		std::make_pair<>("quantum-cycles", "5"),
		std::make_pair<>("batch-process-freq", "1"),
		std::make_pair<>("min-ins", "1000"),
		std::make_pair<>("max-ins", "2000"),
		std::make_pair<>("delay-per-exec", "0"),

		// MCO2 configs
		std::make_pair<>("max-overall-mem", "16384"),
		std::make_pair<>("mem-per-frame", "16"),
		std::make_pair<>("min-mem-per-proc", "4096"),
		std::make_pair<>("max-mem-per-proc", "4096")
	};
};

#endif //CONSOLEMANAGER_H
