#pragma once

#include <vector>

#include "vulkan/vulkan_raii.hpp"

namespace engine::graphics
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

    protected:
        void CreateInstance();
        void SetupDebugMessenger();
        void CreateSurface();
        void PickPhysicalDevice();
        void CreateLogicalDevice();

        std::vector<const char *> GetRequiredExtensions();
        uint32_t FindQueueFamilies(vk::raii::PhysicalDevice physicalDevice);

        const std::vector<char const *> m_DeviceExtensions = {vk::KHRSwapchainExtensionName};

        vk::raii::Context m_Context;
        vk::raii::Instance m_Instance;
        vk::raii::DebugUtilsMessengerEXT m_DebugMessenger;
        vk::raii::SurfaceKHR m_Surface;
        vk::raii::PhysicalDevice m_PhysicalDevice;
        vk::raii::Device m_Device;
        vk::raii::Queue m_GraphicsQueue;
        vk::raii::Queue m_PresentQueue;
    };
}