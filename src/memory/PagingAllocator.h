#ifndef PAGINGALLOCATOR_H
#define PAGINGALLOCATOR_H

#include <unordered_map>

#include "IMemoryAllocator.h"
#include "../process/Process.h"

class PagingAllocator : public IMemoryAllocator{
public:
    explicit PagingAllocator(size_t maxMemorySize);

    void* allocate(Process* process);
    void deallocate(Process* process);
    void visualizeMemory() const;

private:
    size_t maxMemorySize;
    size_t numFrames;
    std::unordered_map<size_t, size_t> frameMap;
    std::vector<size_t> freeFrameList;

    size_t allocateFrames(size_t numFrames, size_t processId, const std::vector<size_t>& pageSizes);
    void deallocateFrames(size_t numFrames, size_t frameIndex, const std::vector<size_t>& pageSizes);
};
#endif //PAGINGALLOCATOR_H
