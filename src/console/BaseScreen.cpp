#include "BaseScreen.h"

#include "../util/string-tokenizer.h"

#include "../console/ConsoleManager.h"

BaseScreen::BaseScreen(const std::shared_ptr<Process>& process, const std::string& processName) {
    this->attachedProcess = process;
    this->name = processName;
}

void BaseScreen::onEnabled() {
    printProcessInfo();
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
    std::cout << "Process: " << attachedProcess->getName() << "\n";
    std::cout << "ID: " << attachedProcess->getId() << "\n\n";

    if (attachedProcess->isFinished()) {
        std::cout << "Finished!" << "\n\n";
    }
    else {
        std::cout << "Current instruction line: " << attachedProcess->getCurrentInstructionLine() << "\n";
        std::cout << "Lines of code: " << attachedProcess->getMaxInstructionLine() << "\n";
    }
    
    // Time created is not seen in the screenshot in the specs, but can reenable if needed
    // std::cout << "Time created: " << attachedProcess->getTimeCreated() << "\n";

    std::cout << "\n";
}

void BaseScreen::printCommandPrefix() {
    std::cout << "user@CSOPESY:~$ ";
}

