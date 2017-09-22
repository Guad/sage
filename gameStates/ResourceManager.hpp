#pragma once

#include <vector>

class ResourceManager
{
public:
    void Track(void *resource);
    void Dispose();
    ~ResourceManager();
    ResourceManager();
private:
    bool _disposed;
    std::vector<void*> _resources;
};