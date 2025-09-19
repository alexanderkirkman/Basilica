#include "Basilica/Core/Application.h"

#include <iostream>

namespace Basilica
{

    Application::Application() {
        std::cout << "Application Init Ran Succesfully" << std::endl;
    }

    void Application::run() {
        handleEvents();
        render();
    }

    void Application::handleEvents() {}

    void Application::render() {}
    
} // namespace Basilica
