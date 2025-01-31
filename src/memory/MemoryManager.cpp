#include "MemoryManager.h"

#include "FirstFitFlatAllocator.h"
#include <set>
#include <algorithm>
#include <iomanip>

#include "PagingAllocator.h"

MemoryManager *MemoryManager::sharedInstance = nullptr;

MemoryManager::MemoryManager() {
    this->totalMemory = std::stoi(
        ConsoleManager::getInstance()->getConfigs().at("max-overall-mem")
    );

    this->frameSize = std::stoi(
        ConsoleManager::getInstance()->getConfigs().at("mem-per-frame")
    );

    this->memory = new uint8_t[this->totalMemory];

    // TODO: implement paging allocator

    if (frameSize == totalMemory) {
        this->allocator = std::make_shared<FirstFitFlatAllocator>(this->memory, this->totalMemory, this->frameSize);
        this->allocatorType = AllocatorType::FIRST_FIT_FLAT_ALLOCATOR;
    } else {
        // ASSUMED THAT totalMemory IS DIVISIBLE BY frameSize
        this->allocator = std::make_shared<PagingAllocator>(this->totalMemory / this->frameSize);
        this->allocatorType = AllocatorType::PAGING_ALLOCATOR;
    }

    /*
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

    printDetails(std::cout);
    */
    
}

void MemoryManager::printDetails(std::ostream &os) const {
    if (this->allocatorType == AllocatorType::FIRST_FIT_FLAT_ALLOCATOR) {
        // Get allocation map
        const std::vector<int>& allocationMap = this->allocator->getAllocationMap();
        int blockStart = 0;
        int blockValue = -1;

        const auto now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const auto* localTime = std::localtime(&now_time_t);
        os << "Timestamp: " << std::put_time(localTime, "(%m/%d/%Y %I:%M:%S%p)") << "\n";

        // Number of processes in memory is the number of unique integers in memory, aside from -1
        const auto uniqueProcesses = std::set(allocationMap.begin(), allocationMap.end());
        os << "Number of processes in memory: " << uniqueProcesses.size() - uniqueProcesses.count(-1) << "\n";
        os << "Total external fragmentation in KB: " << this->computeExternalFragmentation() << "\n";

        // Print the memory map
        os << "----end---- = " << this->totalMemory << "\n\n";

        for (int i = allocationMap.size() - 1; i > -1; i--) {
            if (allocationMap[i] != blockValue) {
                // print the current block, if the value is not -1
                if (blockValue != -1) {
                    os << blockStart << "\n";
                    os << "P" << blockValue << "\n";
                    os << (i + 1) << "\n\n";
                }

                blockStart = i + 1;
                blockValue = allocationMap[i];
            }
        }

        // print last block, if possible
        if (blockValue != -1) {
            os << blockStart << "\n";
            os << "P" << blockValue << "\n";
            os << 0 << "\n\n";
        }

        os << "----start---- = 0" << "\n";
    }
    else {
        // not implemented
    }
}

std::unordered_map<int, int> MemoryManager::getProcessMemoryUsage() const
{
    auto output = std::unordered_map<int, int>();

    if (this->allocatorType == AllocatorType::FIRST_FIT_FLAT_ALLOCATOR) {
        const std::vector<int>& allocationMap = this->allocator->getAllocationMap();

        for (int processId : allocationMap) {
            if (processId != -1) {
                if (output.contains(processId)) {
                    output[processId] += 1;
                }
                else {
                    output[processId] = 1;
                }
            }
        }
    }

    else {
        std::shared_ptr<PagingAllocator> pagingAllocator = std::static_pointer_cast<PagingAllocator>(this->allocator);
        auto frameMap = pagingAllocator->getFrameMap();

        for (auto entry : frameMap) {
            const int processId = entry.second;
            if (processId != -1) {
                if (output.contains(processId)) {
                    output[processId] += Process::pageSize;
                }
                else {
                    output[processId] = Process::pageSize;
                }
            }
        }
    }

    return output;
}

int MemoryManager::computeExternalFragmentation() const {
    const std::vector<int>& allocationMap = this->allocator->getAllocationMap();

    return std::count(allocationMap.begin(), allocationMap.end(), -1);
}

size_t MemoryManager::getTotalMemory() const
{
    return this->totalMemory;
}

std::shared_ptr<IMemoryAllocator> MemoryManager::getAllocator() const {
    return this->allocator;
}

void MemoryManager::initialize() {
    sharedInstance = new MemoryManager();
}

MemoryManager *MemoryManager::getInstance() {
    return sharedInstance;
}

void MemoryManager::destroy() {
    if (sharedInstance->memory != nullptr) {
        delete sharedInstance->memory;
    }

    if (sharedInstance != nullptr) {
        delete sharedInstance;
    }
}

MemoryManager::AllocatorType MemoryManager::getAllocatorType()
{
    return this->allocatorType;
}
