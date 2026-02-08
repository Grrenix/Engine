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
        void CreateSwapChain();
        void CreateImageViews();

        std::vector<const char *> GetRequiredExtensions();
        uint32_t FindQueueFamilies(vk::raii::PhysicalDevice physicalDevice);
        vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats);
        vk::PresentModeKHR ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes);
        vk::Extent2D ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities);

        const std::vector<char const *> m_DeviceExtensions = {vk::KHRSwapchainExtensionName};

        vk::raii::Context m_Context;
        vk::raii::Instance m_Instance;
        vk::raii::DebugUtilsMessengerEXT m_DebugMessenger;
        vk::raii::SurfaceKHR m_Surface;
        vk::raii::PhysicalDevice m_PhysicalDevice;
        vk::raii::Device m_Device;
        vk::raii::Queue m_GraphicsQueue;
        uint32_t m_GraphicsFamilyIndex = 0;
        vk::raii::Queue m_PresentQueue;
        uint32_t m_PresentFamilyIndex = 0;
        vk::raii::SwapchainKHR m_SwapChain;
        std::vector<vk::Image> m_SwapChainImages;
        std::vector<vk::raii::ImageView> m_SwapChainImageViews;

        vk::SurfaceFormatKHR m_SwapChainSurfaceFormat;
        vk::Extent2D m_SwapChainExtent;
    };
}