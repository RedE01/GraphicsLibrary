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
        X11Window(const char* title, Vector2i size, Vector2i pos);
        ~X11Window();

        virtual std::unique_ptr<Image> createImage(Vector2i size) override;

        virtual void drawImage(Image* image, Vector2i pos) override;
        virtual void drawString(const char* string, Vector2i pos) override;

        virtual void setWindowSize(Vector2i size) override;
        virtual void setWindowPos(Vector2i pos) override;

    protected:
        virtual void open() override;
        virtual void draw() override;
        virtual void pollEvents() override;
        virtual void setFullscreen(bool fullscreen) override;

    private:
        x11::Display* m_display;
        int m_screen;
        x11::Window m_window;
        x11::XVisualInfo m_vInfo;
        x11::GC m_gc;
        x11::Atom m_wmDeleteWindow;
        KeycodeMapper m_keycodeMapper;
    };

}