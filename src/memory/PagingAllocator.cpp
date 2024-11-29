#include "PagingAllocator.h"

#include <iostream>

PagingAllocator::PagingAllocator(size_t maxMemorySize)
: maxMemorySize(maxMemorySize), numFrames(maxMemorySize) {
    for (size_t i = 0; i < numFrames; ++i) {
        freeFrameList.push_back(i);
    }
}

void* PagingAllocator::allocate(Process* process) {
    size_t processId = process->getId();
    size_t numFramesNeeded = process->getNumPages();
    if (numFramesNeeded > freeFrameList.size()) {
        std::cerr <<  "Memory allocation failed. Not enough free frames.\n";
        return nullptr;
    }

    // Allocate frames for the process
    size_t frameIndex = allocateFrames(numFramesNeeded, processId, process->getPageSizes());
    return reinterpret_cast<void*>(frameIndex);
}

void PagingAllocator::deallocate(Process* process) {
    size_t processId = process->getId();

    // Find frames allocated to the process and deallocate
    auto it = std::find_if(frameMap.begin(), frameMap.end(), [processId](const auto& entry) { return entry.second == processId; });

    while (it != frameMap.end()) {
        size_t frameIndex = it->first;
        deallocateFrames(1, frameIndex, process->getPageSizes());
        it = std::find_if(frameMap.begin(), frameMap.end(), [processId](const auto& entry) { return entry.second == processId; });
    }
}

void PagingAllocator::visualizeMemory() const {
    std::cout << "Memory Visualization:\n";
    for (size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex) {
        auto it = frameMap.find(frameIndex);
        if (it != frameMap.end()) {
            std::cout << "Frame " << frameIndex << " -> Process " << it->second << "\n";
        } else {
            std::cout << "Frame " << frameIndex << " -> Free\n";
        }
    }
    std::cout << "---------------------------------\n";
}

size_t PagingAllocator::allocateFrames(size_t numFrames, size_t processId, const std::vector<size_t> &pageSizes) {
    size_t frameIndex = freeFrameList.back();
    freeFrameList.pop_back();

    // Map allocated frames to the process ID
    for (size_t i = 0; i < numFrames; ++i) {
        frameMap[frameIndex + i] = processId;
    }
    return frameIndex;
}

void PagingAllocator::deallocateFrames(size_t numFrames, size_t frameIndex, const std::vector<size_t> &pageSizes) {
    //Remove mapping of deallocated frames
    for (size_t i = 0; i < numFrames; ++i) {
        frameMap.erase(frameIndex + i);
    }

    //Add frames back to the free frame list
    for (size_t i = 0; i < numFrames; ++i) {
        freeFrameList.push_back(frameIndex + i);
    }
}



