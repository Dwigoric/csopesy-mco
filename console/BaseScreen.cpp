#include "BaseScreen.h"

#include "../util/string-tokenizer.h"

#include "../console/ConsoleManager.h"

BaseScreen::BaseScreen(const std::shared_ptr<Process>& process, const std::string& processName) {
}

void BaseScreen::onEnabled() {
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
