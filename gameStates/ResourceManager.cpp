#include "ResourceManager.hpp"
#include <stdlib.h>

ResourceManager::ResourceManager()
{
    this->_disposed = false;
}

ResourceManager::~ResourceManager()
{
    if (!this->_disposed)
        this->Dispose();
}

void ResourceManager::Track(void *resource)
{
    this->_resources.push_back(resource);
}

void ResourceManager::Dispose()
{
    if (this->_disposed) return;

    std::size_t len = this->_resources.size();

    for (std::size_t i = 0; i < len; i++)
    {
        //delete this->_resources[i];
        free(this->_resources[i]);
    }

    this->_resources.clear();
    this->_disposed = true;
}