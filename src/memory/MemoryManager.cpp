#include "MemoryManager.h"

MemoryManager* MemoryManager::sharedInstance = nullptr;

MemoryManager::MemoryManager() {
    this->totalMemory = std::stoi(
        ConsoleManager::getInstance()->getConfigs().at("max-overall-mem")
    );

    this->frameSize = std::stoi(
        ConsoleManager::getInstance()->getConfigs().at("mem-per-frame")
    );

    this->memory = new uint8_t[this->totalMemory];
}

void MemoryManager::initialize()
{
    sharedInstance = new MemoryManager();
}

MemoryManager* MemoryManager::getInstance()
{
    return sharedInstance;
}

void MemoryManager::destroy()
{
    if (sharedInstance->memory != nullptr) {
        delete sharedInstance->memory;
    }

    if (sharedInstance != nullptr) {
        delete sharedInstance;
    }
}
