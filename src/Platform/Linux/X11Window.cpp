#include "X11Window.h"
#include "../../Event/ApplicationEvent.h"
#include <assert.h>
#include <cstdlib>

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
        int matchVInfoRet = x11::XMatchVisualInfo(m_display, m_screen, screenBitDepth, TrueColor, &m_vInfo);
        assert(matchVInfoRet);

        // Set window attributes
        m_windowAttributes.background_pixel = 0;
        m_windowAttributes.bit_gravity = StaticGravity; // Keep window content on resize
        m_windowAttributes.colormap = XCreateColormap(m_display, rootWindow, m_vInfo.visual, AllocNone);
        m_windowAttributes.event_mask = StructureNotifyMask; // Tell the server which events to inform us about
        unsigned long attributeMask = CWBitGravity | CWBackPixel | CWColormap | CWEventMask;

        // Create Window
        m_window = x11::XCreateWindow(m_display, rootWindow, pos.x, pos.y, size.x, size.y, 0, m_vInfo.depth, InputOutput, m_vInfo.visual, attributeMask, &m_windowAttributes);
        x11::XStoreName(m_display, m_window, title);

        // This is used to intercept window closing requests so that they can be handled by the user
        m_wmDeleteWindow = x11::XInternAtom(m_display, "WM_DELETE_WINDOW", true);
        x11::XSetWMProtocols(m_display, m_window, &m_wmDeleteWindow, 1);

        // Create graphics context
        m_gc = x11::XDefaultGC(m_display, m_screen);

        initWindowBuffer();
    }

    X11Window::~X11Window() {
        if(m_windowBuffer != nullptr) {
            free(m_windowBuffer);
        }
    }

    void X11Window::open() {
        // Make the window appear on the screen
        x11::XMapWindow(m_display, m_window);
        x11::XFlush(m_display);
    }

    void X11Window::draw() {
        if(!m_windowBuffer) return;
        
        Vector2i size = getWindowSize();
        for(int i = 0; i < size.x; ++i) {
            for(int j = 0; j < size.y; ++j) {
                unsigned int* pixel = (unsigned int*)(m_windowBuffer+(i*bytesPerPixel)+(j*bytesPerPixel*size.x));
                *pixel = 0x00ff0000;
            }
        }
        int t = x11::XPutImage(m_display, m_window, m_gc, m_xWindowBuffer, 0, 0, 0, 0, size.x, size.y);        
    }

    void X11Window::pollEvents() {
        while(x11::XPending(m_display) > 0) {
            x11::XEvent e;
            x11::XNextEvent(m_display, &e);
            if(e.xany.window != m_window) continue;

            switch (e.type) {
            case ClientMessage: {
                x11::XClientMessageEvent* cme = (x11::XClientMessageEvent*)&e;
                if(cme->data.l[0] == m_wmDeleteWindow) {
                    windowOpen = false;
                    x11::XDestroyWindow(m_display, m_window);
                    WindowCloseEvent wce;
                    m_eventCallback(&wce);
                    break;
                }
            }
            case ConfigureNotify: {
                x11::XConfigureEvent* ce = (x11::XConfigureEvent*)&e;
                m_size.x = ce->width;
                m_size.y = ce->height;
                initWindowBuffer();
                break;
            }
            }
        }
    }

    char* X11Window::getWindowBuffer() {
        return m_windowBuffer;
    }

    void X11Window::initWindowBuffer() {
        if(m_windowBuffer != nullptr) {
            XDestroyImage(m_xWindowBuffer);
            m_windowBuffer = nullptr;
        }
        m_windowBuffer = (char*)malloc(getWindowBufferSize());

        Vector2i size = getWindowSize();
        m_xWindowBuffer = x11::XCreateImage(m_display, m_vInfo.visual, m_vInfo.depth, ZPixmap, 0, m_windowBuffer, size.x, size.y, bytesPerPixel * 8, 0);
    }

}