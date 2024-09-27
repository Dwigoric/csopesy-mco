// AConsole.h : Abstract class describing generic console interfaces.
#ifndef ACONSOLE_H
#define ACONSOLE_H

#include <string>

class AConsole {
public:
	AConsole() = default;
	AConsole(std::string name);
	~AConsole() = default;

	std::string getName() {
		return name;
	};

	// onEnabled() is called whenever the console is initially loaded on the screen.
	virtual void onEnabled() = 0;

	// display() is called once every frame to display the console's output.
	virtual void display() = 0;

	// process() is called every frame to process console logic.
	virtual void process() = 0;

	std::string name;
	friend class ConsoleManager;
};

#endif //ACONSOLE_H
