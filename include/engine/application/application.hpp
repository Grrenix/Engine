#pragma once

namespace engine
{
    class Application
    {
    public:
        // Builder
        static Application *New();
        Application *WithWindowSpec(class WindowSpec *Spec);

        void Run();

    private:
        Application() {};

    private:
        class Window *m_Window = nullptr;
    };
}