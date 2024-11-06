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

    this->allocator = std::make_shared<FirstFitFlatAllocator>(this->memory, this->totalMemory, this->frameSize);

    /* 
    --- FOR TESTING
    uint8_t* mem = static_cast<uint8_t*>(this->allocator->allocate(0, 4096));
    std::fill(mem, mem + 4096, 'a');

    uint8_t* mem2 = static_cast<uint8_t*>(this->allocator->allocate(1, 4096));
    std::fill(mem2, mem2 + 4096, 'b');

    uint8_t* mem3 = static_cast<uint8_t*>(this->allocator->allocate(2, 4096));
    std::fill(mem3, mem3 + 4096, 'c');

    this->allocator->deallocate(0);
    this->allocator->deallocate(1);

    uint8_t* mem4 = static_cast<uint8_t*>(this->allocator->allocate(3, 4096));
    std::fill(mem4, mem4 + 4096, 'd');

    std::cout << this->allocator->visualizeMemory();
    std::cout << this->allocator->getAllocatedSize() << "\n";
    */
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
