#pragma once
#include "../Macro.h"
#include "../Window.h"
#include <vulkan/vulkan.hpp>

namespace Engine {
    class GfxBase
    {
    public:
        GfxBase(Window* pWindow);
        ~GfxBase();

        GfxBase(const GfxBase&) = delete;
        GfxBase operator=(const GfxBase&) = delete;

        void StartRender();
        void EndRender();

    private:
        void CreateInstance();
        void FindSuitablePhysicalDevice();
        void CreateDeviceInterface();

    private:
        VkInstance mInstance;
        VkDevice mDevice;
        VkPhysicalDevice mPhysicalDevice;
    };
}