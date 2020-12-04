#include "Window.h"

#ifdef RGL_LINUX
    #include "Platform/Linux/X11Window.h"
#endif

namespace rgl {

    Window::Window(const char* title, Vector2i pos, Vector2i size) : m_pos(pos), m_size(size) {
    }

    std::unique_ptr<Window> Window::Create(const char* title, Vector2i pos, Vector2i size) {
        #ifdef RGL_LINUX
            return std::make_unique<X11Window>(title, pos, size);
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

}