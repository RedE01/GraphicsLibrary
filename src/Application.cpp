#include "Application.h"
#include "Window.h"
#include "Input/Input.h"

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