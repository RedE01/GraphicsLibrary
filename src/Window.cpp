#include "Window.h"

#ifdef RGL_LINUX
    #include "Platform/Linux/X11Window.h"
#endif

namespace rgl {

    Window::Window(const char* title, Vector2i size, Vector2i pos) : m_pos(pos), m_size(size), m_isFullscreen(false) {
    }

    std::unique_ptr<Window> Window::Create(const char* title, Vector2i size, Vector2i pos) {
        #ifdef RGL_LINUX
            return std::make_unique<X11Window>(title, size, pos);
        #else
            return nullptr;
        #endif
    }

    void Window::setEventCallback(const EventCallbackFunction& callback) {
        m_eventCallback = callback;
    }

    Vector2i Window::getWindowSize() const {
        return m_size;
    }

    Vector2i Window::getWindowPos() const {
        return m_pos;
    }

    int Window::getWindowBufferSize() const {
        return m_size.x * m_size.y * bytesPerPixel;
    }

    bool Window::isFullscreen() const {
        return m_isFullscreen;
    }

}