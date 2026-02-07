#include "engine/graphics/renderer.hpp"

#include <iostream>

#include "GLFW/glfw3.h"
#include "vulkan/vulkan_raii.hpp"

#ifndef NDEBUG
const std::vector<char const *> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};
#endif

const std::vector<char const *> DEVICE_EXTENSIONS = {vk::KHRSwapchainExtensionName};

namespace engine::graphics
{
    static VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
                                                          vk::DebugUtilsMessageTypeFlagsEXT type,
                                                          const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                          void *)
    {
        std::cerr << "Validation layer: type " << to_string(type) << " msg: " << pCallbackData->pMessage << '\n';

        return vk::False;
    }

    Renderer::Renderer() : m_Context(std::make_unique<vk::raii::Context>())
    {
        CreateInstance();
        SetupDebugMessenger();
        PickPhysicalDevice();
    }

    void Renderer::CreateInstance()
    {
        constexpr vk::ApplicationInfo appInfo{.pApplicationName = "GameA",
                                              .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                              .pEngineName = "Engine",
                                              .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                              .apiVersion = vk::ApiVersion14};

#ifndef NDEBUG
        std::vector<const char *> requiredLayers;

        requiredLayers.assign(VALIDATION_LAYERS.begin(), VALIDATION_LAYERS.end());

        auto layerProperties = m_Context->enumerateInstanceLayerProperties();

        if (std::ranges::any_of(requiredLayers, [&layerProperties](auto const &requiredLayer)
                                { return std::ranges::none_of(layerProperties, [requiredLayer](auto const &layerProperty)
                                                              { return strcmp(layerProperty.layerName, requiredLayer) == 0; }); }))
        {
            throw std::runtime_error("One or more required layers are not supported!");
        }

#endif
        auto requiredExtensions = GetRequiredExtensions();

        auto extensionPropeties = m_Context->enumerateInstanceExtensionProperties();
        for (uint32_t i = 0; i < requiredExtensions.size(); ++i)
        {
            if (std::ranges::none_of(extensionPropeties,
                                     [glfwExtension = requiredExtensions[i]](auto const &extensionProperty)
                                     {
                                         return strcmp(extensionProperty.extensionName, glfwExtension) == 0;
                                     }))
            {
                throw std::runtime_error("Required extension not suported: " + std::string(requiredExtensions[i]));
            }
        }

        vk::InstanceCreateInfo createInfo{.pApplicationInfo = &appInfo,
#ifndef NDEBUG
                                          .enabledLayerCount = static_cast<uint32_t>(requiredLayers.size()),
                                          .ppEnabledLayerNames = requiredLayers.data(),
#endif
                                          .enabledExtensionCount = (uint32_t)requiredExtensions.size(),
                                          .ppEnabledExtensionNames = requiredExtensions.data()};

        m_Instance.reset(new vk::raii::Instance(*m_Context, createInfo));
    }

    void Renderer::SetupDebugMessenger()
    {
#ifdef NDEBUG
        return;
#else
        vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);

        vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                                           vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                                                           vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

        vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT{
            .messageSeverity = severityFlags, .messageType = messageTypeFlags, .pfnUserCallback = &DebugCallback};
        m_DebugMessenger = std::make_unique<vk::raii::DebugUtilsMessengerEXT>(
            m_Instance->createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT));
#endif
    }

    void Renderer::PickPhysicalDevice()
    {
        auto devices = m_Instance->enumeratePhysicalDevices();

        const auto devIter = std::ranges::find_if(devices, [&](auto const &device)
                                                  {
        auto queueFamilies = device.getQueueFamilyProperties();
        bool isSuitable = device.getProperties().apiVersion >= VK_API_VERSION_1_3;

        const auto qfpIter = std::ranges::find_if(queueFamilies, [](vk::QueueFamilyProperties const &qfp) {
            return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0);
        });

        isSuitable = isSuitable && (qfpIter != queueFamilies.end());

        auto extensions = device.enumerateDeviceExtensionProperties();
        bool found = true;
        for (auto const &extension : DEVICE_EXTENSIONS)
        {
            auto extensionIter = std::ranges::find_if(
                extensions, [extension](auto const &ext) { return strcmp(ext.extensionName, extension) == 0; });
            found = found && extensionIter != extensions.end();
        }
        isSuitable = isSuitable && found;

        if (isSuitable)
        {
            m_PhysicalDevice = std::make_unique<vk::raii::PhysicalDevice>(device);
        }

        return isSuitable; });

        if (devIter == devices.end())
        {
            throw std::runtime_error("Failed to find a suitable GPU");
        }
    }

    std::vector<const char *> Renderer::GetRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
#ifndef NDEBUG
        extensions.push_back(vk::EXTDebugUtilsExtensionName);
#endif

        return extensions;
    }

    Renderer::~Renderer()
    {
    }
}
