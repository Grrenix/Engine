
#include <vector>

namespace vk::raii
{
    class Context;
    class DebugUtilsMessengerEXT;
    class Instance;
    class PhysicalDevice;
} // namespace vk::raii

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
        void PickPhysicalDevice();

        std::vector<const char *> GetRequiredExtensions();

        std::unique_ptr<vk::raii::Context> m_Context;
        std::unique_ptr<vk::raii::Instance> m_Instance;
        std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> m_DebugMessenger;
        std::unique_ptr<vk::raii::PhysicalDevice> m_PhysicalDevice;
    };
}