#include "Application.h"
#include "Window.h"
#include "Input/Input.h"

namespace rgl {

    Application::Application() {

    }

    void Application::create(const char* title, Vector2i size, Vector2i pos) {
        window = Window::Create(title, size, pos);
    }

    void Application::run() {
        if(window.get()) {
            window->open();
        }
        window->setEventCallback([this](Event* e){ return this->handleEvent(e); });

        while(window->windowOpen) {
            onUpdate();
            window->draw();
            
            Input::Update();
            window->pollEvents();
        }
    }

    void Application::handleEvent(Event* event) {
        if(event->isInCategory(EventCategory::EventCategoryKeyboard)) {
            Input::HandleEvent(event);
        }
        
        onEvent(event);
    }
    
}