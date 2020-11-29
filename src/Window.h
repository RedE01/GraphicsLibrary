#pragma once
#include "Etc/Vector.h"
#include "Event/Event.h"
#include <memory>
#include <functional>

namespace rgl {

    class Window {
    protected:
        Window(const char* title, Vector2i pos, Vector2i size);

    public:
        using EventCallbackFunction = std::function<void(Event*)>;

        static std::unique_ptr<Window> Create(const char* title, Vector2i pos, Vector2i size);
        virtual void open() = 0;
        virtual void pollEvents() = 0;
        void setEventCallback(const EventCallbackFunction& callback);

    public:
        bool windowOpen = true;
        Vector2i pos, size;
    
    protected:
        EventCallbackFunction m_eventCallback;
    };

}