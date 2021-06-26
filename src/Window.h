#pragma once
#include "Etc/Vector.h"
#include "Event/Event.h"
#include <memory>
#include <functional>

namespace rgl {

    class Window {
    protected:
        using EventCallbackFunction = std::function<void(Event*)>;

        Window(const char* title, Vector2i size, Vector2i pos);
        
        static std::unique_ptr<Window> Create(const char* title, Vector2i size, Vector2i pos);
        
        virtual void open() = 0;
        virtual void draw() = 0;
        virtual void pollEvents() = 0;

        void setEventCallback(const EventCallbackFunction& callback);

        friend class Application;

    public:
        virtual void setPixel(int x, int y, Vector3 val) = 0;
        virtual void setPixel(const Vector2i& pos, Vector3 val) = 0;

        virtual char* getWindowBuffer() = 0;
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