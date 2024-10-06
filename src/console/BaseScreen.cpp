#include "BaseScreen.h"

#include "../util/string-tokenizer.h"

#include "../console/ConsoleManager.h"

BaseScreen::BaseScreen(const std::shared_ptr<Process>& process, const std::string& processName) {
    this->attachedProcess = process;
    this->name = processName;
}

void BaseScreen::onEnabled() {
    std::cout << "Process: " << attachedProcess->getName() << "\n";
    std::cout << "ID: " << attachedProcess->getId() << "\n\n";
    std::cout << "Current instruction line: " << attachedProcess->getCurrentInstructionLine() << "\n";
    std::cout << "Lines of code: " << attachedProcess->getMaxInstructionLine() << "\n";
    std::cout << "Time created: " << attachedProcess->getTimeCreated() << "\n";
}

void BaseScreen::display() {
}

void BaseScreen::process() {
    std::string fullCommand;

    printCommandPrefix();

    std::getline(std::cin, fullCommand);

    const std::vector<std::string> commandTokens = tokenize(fullCommand, "[ ]+");
    const std::string& command = commandTokens[0];

    if (command == "process-smi") printProcessInfo();
    else if (command == "exit") ConsoleManager::getInstance()->returnToPreviousConsole();
    else if (command == "help") {
        std::cout << "Available commands:\n";
        std::cout << "process-smi: Display process information\n";
        std::cout << "exit: Return to previous console\n";
    }
    else {
        std::cout << "Invalid command. Type 'help' for a list of commands.\n";
    }
}

void BaseScreen::printProcessInfo() {
    // TODO: Implement this function
}

void BaseScreen::printCommandPrefix() {
    std::cout << "user@CSOPESY:~$ ";
}
