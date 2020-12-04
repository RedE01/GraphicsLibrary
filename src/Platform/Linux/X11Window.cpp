#include "X11Window.h"
#include "../../Event/ApplicationEvent.h"
#include <assert.h>

namespace rgl {

    X11Window::X11Window(const char* title, Vector2i pos, Vector2i size) : Window(title, pos, size) {
        m_display = x11::XOpenDisplay(0);
        assert(m_display);

        m_screen = x11::XDefaultScreen(m_display);
        x11::Window rootWindow = x11::XDefaultRootWindow(m_display);

        int blackColor = x11::XBlackPixel(m_display, m_screen);
        int whiteColor = x11::XWhitePixel(m_display, m_screen);

        // Set requirements for rendering target
        int screenBitDepth = 24;
        assert(x11::XMatchVisualInfo(m_display, m_screen, screenBitDepth, TrueColor, &m_vInfo));

        // Set window attributes
        m_windowAttributes.background_pixel = 0;
        m_windowAttributes.colormap = XCreateColormap(m_display, rootWindow, m_vInfo.visual, AllocNone);
        m_windowAttributes.event_mask = StructureNotifyMask; // Tell the server which events to inform us about
        unsigned long attributeMask = CWBackPixel | CWColormap | CWEventMask;

        // Create Window
        m_window = x11::XCreateWindow(m_display, rootWindow, pos.x, pos.y, size.x, size.y, 0, m_vInfo.depth, InputOutput, m_vInfo.visual, attributeMask, &m_windowAttributes);
        x11::XStoreName(m_display, m_window, title);

        // This is used to intercept window closing requests so that they can be handled by the user
        x11::Atom wmDelete = x11::XInternAtom(m_display, "WM_DELETE_WINDOW", true);
        x11::XSetWMProtocols(m_display, m_window, &wmDelete, 1);

        // Create graphics context
        m_gc = x11::XCreateGC(m_display, m_window, 0, 0);
        x11::XSetForeground(m_display, m_gc, blackColor);
    }

    void X11Window::open() {
        // Make the window appear on the screen
        x11::XMapWindow(m_display, m_window);
        x11::XFlush(m_display);
    }

    void X11Window::pollEvents() {
        while(x11::XPending(m_display) > 0) {
            x11::XEvent e;
            x11::XNextEvent(m_display, &e);
            if(e.xany.window != m_window) continue;

            switch (e.type) {
            case ClientMessage: {
                windowOpen = false;
                x11::XDestroyWindow(m_display, m_window);
                WindowCloseEvent wce;
                m_eventCallback(&wce);
                break;
            }
            }
        }
    }

}