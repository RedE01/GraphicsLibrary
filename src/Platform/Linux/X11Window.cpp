#include "X11Window.h"
#include "../../Event/ApplicationEvent.h"
#include "../../Event/InputEvent.h"
#include <assert.h>
#include <cstdlib>
#include <limits>
#include <cstring>

namespace x11 {
    #include <X11/Xatom.h>
}
typedef x11::Atom Atom;

namespace rgl {

    X11Window::X11Window(const char* title, Vector2i size, Vector2i pos) : Window(title, size, pos) {
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
        m_windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask; // Tell the server which events to inform us about
        unsigned long attributeMask = CWBitGravity | CWBackPixel | CWColormap | CWEventMask;

        // Create Window
        m_window = x11::XCreateWindow(m_display, rootWindow, pos.x, pos.y, size.x, size.y, 0, m_vInfo.depth, InputOutput, m_vInfo.visual, attributeMask, &m_windowAttributes);
        x11::XStoreName(m_display, m_window, title);

        // This is used to intercept window closing requests so that they can be handled by the user
        m_wmDeleteWindow = x11::XInternAtom(m_display, "WM_DELETE_WINDOW", true);
        x11::XSetWMProtocols(m_display, m_window, &m_wmDeleteWindow, 1);

        // Force position of window
        if(pos.x != std::numeric_limits<int>::max() && pos.y != std::numeric_limits<int>::max()) {
            x11::XSizeHints sizeHints = {0};
            sizeHints.flags = PPosition;
            sizeHints.x = pos.x;
            sizeHints.y = pos.y;

            x11::XSetNormalHints(m_display, m_window, &sizeHints);
        }

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
                if(m_size.x != ce->width || m_size.y != ce->height) {
                    m_size.x = ce->width;
                    m_size.y = ce->height;
                    initWindowBuffer();
                    WindowResizeEvent wre;
                    m_eventCallback(&wre);
                }
                break;
            }
            case KeyPress: {
                x11::KeySym ks = x11::XLookupKeysym(&e.xkey, 0);
                KeyPressedEvent kpe(m_keycodeMapper.getKey(ks));
                m_eventCallback(&kpe);
                break;
            }
            case KeyRelease: {
                x11::KeySym ks = x11::XLookupKeysym(&e.xkey, 0);
                KeyReleasedEvent kre(m_keycodeMapper.getKey(ks));
                m_eventCallback(&kre);
                break;
            }
            }
        }
    }

    void X11Window::setFullscreen(bool fullscreen) {
        x11::Atom wmState = x11::XInternAtom(m_display, "_NET_WM_STATE", true);
        x11::Atom wmFullscreen = x11::XInternAtom(m_display, "_NET_WM_STATE_FULLSCREEN", False);

        x11::XEvent xev;
        std::memset(&xev, 0, sizeof(xev));
        xev.type = ClientMessage;
        xev.xclient.window = m_window;
        xev.xclient.message_type = wmState;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = fullscreen ? 1 : 0;
        xev.xclient.data.l[1] = wmFullscreen;
        xev.xclient.data.l[2] = 0;

        x11::XSendEvent(m_display, x11::XDefaultRootWindow(m_display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

        m_isFullscreen = fullscreen;
    }

    void X11Window::setPixel(int x, int y, Vector3 val) {
        if(x < 0 || x >= m_size.x || y < 0 || y >= m_size.y) return;

        val *= 255.0;
        unsigned int pixelVal = 0xFF000000 | ((unsigned int)val.x << 16) | ((unsigned int)val.y << 8) | (unsigned int)val.z;

        int offset = (x + y * m_size.x) * bytesPerPixel;
        *((unsigned int*)(m_windowBuffer + offset)) = pixelVal;
    }

    void X11Window::setPixel(const Vector2i& pos, Vector3 val) {
        setPixel(pos.x, pos.y, val);
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