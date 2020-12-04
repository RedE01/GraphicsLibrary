#include "Application.h"
#include "Window.h"

namespace rgl {

    Application::Application() {

    }

    void Application::create(const char* title, Vector2i pos, Vector2i size) {
        window = Window::Create(title, pos, size);
    }

    void Application::run() {
        if(window.get()) {
            window->open();
        }
        window->setEventCallback([this](Event* e){ return this->onEvent(e); });

        while(window->windowOpen) {
            onUpdate();
            window->draw();
            
            window->pollEvents();
        }
    }
    
}