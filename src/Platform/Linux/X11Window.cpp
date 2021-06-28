#include "X11Window.h"
#include "../../Event/ApplicationEvent.h"
#include "../../Event/InputEvent.h"
#include "X11Image.h"
#include <assert.h>
#include <cstdlib>
#include <limits>
#include <cstring>

namespace x11 {
    #include <X11/Xatom.h>
}
typedef x11::Atom Atom;

unsigned long rgb(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 16) + (g << 8) + b;
}

namespace rgl {

    X11Window::X11Window(const char* title, Vector2i size, Vector2i pos) : Window(title, size, pos) {
        m_display = x11::XOpenDisplay(0);
        assert(m_display);

        m_screen = x11::XDefaultScreen(m_display);
        x11::Window rootWindow = x11::XDefaultRootWindow(m_display);

        // Set requirements for rendering target
        int screenBitDepth = 24;
        int matchVInfoRet = x11::XMatchVisualInfo(m_display, m_screen, screenBitDepth, TrueColor, &m_vInfo);
        assert(matchVInfoRet);

        // Set window attributes
        x11::XSetWindowAttributes windowAttributes;
        windowAttributes.background_pixel = x11::XWhitePixel(m_display, m_screen);
        windowAttributes.bit_gravity = StaticGravity; // Keep window content on resize
        windowAttributes.colormap = XCreateColormap(m_display, rootWindow, m_vInfo.visual, AllocNone);
        windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask | PointerMotionMask | ButtonPressMask; // Tell the server which events to inform us about
        unsigned long attributeMask = CWBitGravity | CWBackPixel | CWColormap | CWEventMask;

        // Create Window
        m_window = x11::XCreateWindow(m_display, rootWindow, pos.x, pos.y, size.x, size.y, 0, m_vInfo.depth, InputOutput, m_vInfo.visual, attributeMask, &windowAttributes);
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
        m_gc = x11::XCreateGC(m_display, m_window, 0, NULL);

        // Set up default font
        const char* fontName = "fixed";
        x11::XFontStruct* fontInfo = x11::XLoadQueryFont(m_display, fontName);
        if(fontInfo) {
            x11::XSetFont(m_display, m_gc, fontInfo->fid);
        }
    }

    X11Window::~X11Window() {
        x11::XCloseDisplay(m_display);
    }

    void X11Window::open() {
        // Make the window appear on the screen
        x11::XMapWindow(m_display, m_window);
        x11::XFlush(m_display);
    }

    void X11Window::draw() {
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
                    WindowResizeEvent wre;
                    m_eventCallback(&wre);
                }
                break;
            }
            case Expose: {
                if(e.xexpose.count == 0) {
                    WindowExposeEvent wee;
                    m_eventCallback(&wee);
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
            case MotionNotify: {
                MouseMovedEvent mme(rgl::Vector2i(e.xmotion.x, e.xmotion.y), rgl::Vector2i(e.xmotion.x_root, e.xmotion.y_root));
                m_eventCallback(&mme);
                break;
            }
            case ButtonPress: {
                MouseButtonPressedEvent mbpe(m_keycodeMapper.getButton(e.xbutton.button), rgl::Vector2i(e.xbutton.x, e.xbutton.y), rgl::Vector2i(e.xbutton.x_root, e.xbutton.y_root));
                m_eventCallback(&mbpe);
                break;
            }
            case ButtonRelease: {
                MouseButtonReleasedEvent mbre(m_keycodeMapper.getButton(e.xbutton.button), rgl::Vector2i(e.xbutton.x, e.xbutton.y), rgl::Vector2i(e.xbutton.x_root, e.xbutton.y_root));
                m_eventCallback(&mbre);
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

    std::unique_ptr<Image> X11Window::createImage(Vector2i size) {
        return std::make_unique<X11Image>(m_display, &m_vInfo, 4, size);
    }

    void X11Window::drawImage(Image* image, Vector2i pos) {
        x11::XPutImage(m_display, m_window, m_gc, ((X11Image*)image)->m_ximage, 0, 0, pos.x, pos.y, image->getSize().x, image->getSize().y);
    }

    void X11Window::drawString(const char* string, Vector2i pos) {
        x11::XDrawString(m_display, m_window, m_gc, pos.x, pos.y, string, strlen(string));
    }

    void X11Window::drawRectangle(Vector2i pos, Vector2i size) {
        x11::XDrawRectangle(m_display, m_window, m_gc, pos.x, pos.y, size.x, size.y);
    }

    void X11Window::drawRectangleFilled(Vector2i pos, Vector2i size) {
        x11::XFillRectangle(m_display, m_window, m_gc, pos.x, pos.y, size.x, size.y);
    }

    void X11Window::drawCircle(Vector2i pos, Vector2i size) {
        x11::XDrawArc(m_display, m_window, m_gc, pos.x, pos.y, size.x, size.y, 0, 23040);
    }

    void X11Window::drawCircleFilled(Vector2i pos, Vector2i size) {
        x11::XFillArc(m_display, m_window, m_gc, pos.x, pos.y, size.x, size.y, 0, 23040);
    }

    void X11Window::drawLine(Vector2i pos1, Vector2i pos2) {
        x11::XDrawLine(m_display, m_window, m_gc, pos1.x, pos1.y, pos2.x, pos2.y);
    }

    void X11Window::clearScreen() {
        x11::XClearWindow(m_display, m_window);
    }

    void X11Window::setDrawColor(Vector3 color) {
        x11::XSetForeground(m_display, m_gc, rgb(color.x * 255, color.y * 255, color.z * 255));
    }

    void X11Window::setBackgroundColor(Vector3 color) {
        x11::XSetWindowBackground(m_display, m_window, rgb(color.x * 255, color.y * 255, color.z * 255));
    }

    void X11Window::setWindowSize(Vector2i size) {
        x11::XResizeWindow(m_display, m_window, size.x, size.y);
        m_size = size;
    }

    void X11Window::setWindowPos(Vector2i pos) {
        x11::XMoveWindow(m_display, m_window, pos.x, pos.y);
        m_pos = pos;
    }

}