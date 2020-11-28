#include "X11Window.h"
#include <assert.h>
#include <iostream>

namespace rgl {

    X11Window::X11Window(const char* title, Vector2i pos, Vector2i size) : Window(title, pos, size) {
        m_display = x11::XOpenDisplay(0);
        assert(m_display);

        m_screen = x11::XDefaultScreen(m_display);

        int blackColor = x11::XBlackPixel(m_display, m_screen);
        int whiteColor = x11::XWhitePixel(m_display, m_screen);

        m_window = x11::XCreateSimpleWindow(m_display, x11::XDefaultRootWindow(m_display), pos.x, pos.y, size.x, size.y, 0, blackColor, whiteColor);

        // Tell the server which events to inform us about
        x11::XSelectInput(m_display, m_window, StructureNotifyMask | ExposureMask);

        // Create graphics context
        m_gc = x11::XCreateGC(m_display, m_window, 0, 0);
        x11::XSetForeground(m_display, m_gc, blackColor);
    }

    void X11Window::open() {
        // Make the window appear on the screen
        x11::XMapWindow(m_display, m_window);
        x11::XFlush(m_display);

        // Event loop
        bool windowOpen = true;
        while(windowOpen) {
            x11::XEvent e;
            x11::XNextEvent(m_display, &e);
            if(e.xany.window != m_window) continue;

            switch (e.type) {
            case DestroyNotify:
                windowOpen = false;
                break;
            case Expose:
                x11::XDrawLine(m_display, m_window, m_gc, 10, 10, 50, 50);
                break;
            }
        }
    }

}