#ifndef PAGINGALLOCATOR_H
#define PAGINGALLOCATOR_H

#include <unordered_map>

#include "IMemoryAllocator.h"
#include "../process/Process.h"

class PagingAllocator : public IMemoryAllocator{
public:
    explicit PagingAllocator(size_t maxMemorySize);

    void* allocate(std::shared_ptr<Process> process) override;
    void deallocate(std::shared_ptr<Process> process) override;
    std::string visualizeMemory() override;

    std::vector<int>& getAllocationMap() override;
    size_t getAllocatedSize() override;
    std::unordered_map<size_t, size_t> getFrameMap() const;

private:
    size_t maxMemorySize;
    size_t numFrames;
    std::unordered_map<size_t, size_t> frameMap;
    std::vector<size_t> freeFrameList;

    size_t allocateFrames(size_t numFrames, size_t processId, const std::vector<size_t>& pageSizes);
    void deallocateFrames(size_t numFrames, size_t frameIndex, const std::vector<size_t>& pageSizes);
};
#endif //PAGINGALLOCATOR_H
