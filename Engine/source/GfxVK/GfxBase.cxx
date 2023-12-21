#include "GfxVK/GfxBase.h"
#include <vulkan/vulkan_core.h>

Engine::GfxBase::GfxBase(Engine::Window* pWindow)
{
    CreateInstance();
}

Engine::GfxBase::~GfxBase()
{
    vkDestroyInstance(mInstance, nullptr);
}

void Engine::GfxBase::StartRender(){}
void Engine::GfxBase::EndRender(){}

void Engine::GfxBase::CreateInstance()
{
    
}

