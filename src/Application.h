#pragma once
#include <memory>
#include "Window.h"

namespace rgl {

    class Application {
    public:
        Application();

        void create(const char* title, Vector2i pos, Vector2i size);
        void run();

        virtual void onUpdate() = 0;
        virtual void onEvent(Event* event) = 0;

    public:
        std::unique_ptr<Window> window;
    };

}