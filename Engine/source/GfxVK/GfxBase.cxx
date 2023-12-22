#include "GfxVK/GfxBase.h"
#include "Exception.h"
#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "SFML/Window/Vulkan.hpp"

Engine::GfxBase::GfxBase(Engine::Window* pWindow)
{
    CreateInstance();
    FindSuitablePhysicalDevice();
}

Engine::GfxBase::~GfxBase()
{
    vkDestroyInstance(mInstance, nullptr);
}

void Engine::GfxBase::StartRender(){}
void Engine::GfxBase::EndRender(){}

void Engine::GfxBase::CreateInstance()
{
    
    std::vector<const char*> extensions = sf::Vulkan::getGraphicsRequiredInstanceExtensions();
    
    VkApplicationInfo appInfo = {};
    appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.pApplicationName = "Project";
    appInfo.pEngineName = "Unknown";
    appInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkResult res = vkCreateInstance(&createInfo, nullptr, &mInstance);
    if(res != VK_SUCCESS) throw Exception();
}

void Engine::GfxBase::FindSuitablePhysicalDevice()
{
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(mInstance, &count, nullptr);
    if(count == 0) throw Exception();

    std::vector<VkPhysicalDevice> vDevices(count);
    vkEnumeratePhysicalDevices(mInstance, &count, &vDevices[0]);

    for(const auto device : vDevices)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        printf("Physical adapter found: %s\n", properties.deviceName);
        //For now accept any physical GPU
        if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            mPhysicalDevice = device;
    }


}

void Engine::GfxBase::CreateDeviceInterface()
{
    VkDeviceCreateInfo devInfo = {};
    devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
}