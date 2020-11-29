#pragma once
#include "../../Window.h"

namespace x11 {
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
}

namespace rgl {

    class X11Window : public Window {
    public:
        X11Window(const char* title, Vector2i pos, Vector2i size);

        virtual void open() override;
        virtual void pollEvents() override;

    private:
        x11::Display* m_display;
        int m_screen;
        x11::Window m_window;
        x11::XSetWindowAttributes m_windowAttributes;
        x11::XVisualInfo m_vInfo;
        x11::GC m_gc;
    };

}