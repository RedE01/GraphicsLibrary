#pragma once
#include "Etc/Vector.h"
#include "Event/Event.h"
#include "Image.h"
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
        virtual std::unique_ptr<Image> createImage(Vector2i size) = 0;

        virtual void drawImage(Image* image, Vector2i pos) = 0;
        virtual void drawString(const char* string, Vector2i pos) = 0;

        virtual void setFullscreen(bool fullscreen) = 0;
        virtual void setWindowSize(Vector2i size) = 0;
        virtual void setWindowPos(Vector2i pos) = 0;

        Vector2i getWindowSize() const;
        Vector2i getWindowPos() const;
        bool isFullscreen() const;

    public:
        bool windowOpen = true;
    
    protected:
        EventCallbackFunction m_eventCallback;
        Vector2i m_pos, m_size;
        bool m_isFullscreen;
    };

}