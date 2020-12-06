#pragma once
#include "../../Window.h"
#include "../../Input/KeycodeMapper.h"

namespace x11 {
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
}

namespace rgl {

    class X11Window : public Window {
    public:
        X11Window(const char* title, Vector2i pos, Vector2i size);
        ~X11Window();

        virtual void open() override;
        virtual void draw() override;
        virtual void pollEvents() override;
        virtual char* getWindowBuffer() override;

    private:
        void initWindowBuffer();

    private:
        x11::Display* m_display;
        int m_screen;
        x11::Window m_window;
        x11::XSetWindowAttributes m_windowAttributes;
        x11::XVisualInfo m_vInfo;
        x11::GC m_gc;
        x11::XImage* m_xWindowBuffer;
        char* m_windowBuffer = nullptr;
        x11::Atom m_wmDeleteWindow;
        KeycodeMapper m_keycodeMapper;
    };

}