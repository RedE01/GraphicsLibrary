#include "Window.h"

#ifdef RGL_LINUX
    #include "Platform/Linux/X11Window.h"
#endif

namespace rgl {

    Window::Window(const char* title, Vector2i pos, Vector2i size) : pos(pos), size(size) {
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

}