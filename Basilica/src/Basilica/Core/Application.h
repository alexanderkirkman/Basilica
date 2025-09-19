#pragma once

namespace Basilica 
{   

    class Application
    {
    public:
        Application();
        ~Application() = default;

        void run();
    private:
        void handleEvents();
        void render();
    };    

} // namespace Basilica
