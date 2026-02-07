#include "vulkan/vulkan_raii.hpp"

namespace engine::graphics
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

    protected:
        vk::raii::Context m_Context;
        vk::raii::Instance m_Instance = nullptr;
    };
}