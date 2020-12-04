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
        virtual void draw() = 0;
        virtual void pollEvents() = 0;
        virtual char* getWindowBuffer() = 0;
        void setEventCallback(const EventCallbackFunction& callback);
        Vector2i getWindowSize() const;
        Vector2i getWindowPos() const;
        int getWindowBufferSize() const;

    public:
        bool windowOpen = true;
        const int bytesPerPixel = 4;
    
    protected:
        EventCallbackFunction m_eventCallback;
        Vector2i m_pos, m_size;
    };

}