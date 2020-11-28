#pragma once
#include <memory>
#include "Window.h"

namespace rgl {

    class Application {
    public:
        Application();

        void create(const char* title, Vector2i pos, Vector2i size);
        void run();

    public:
        std::unique_ptr<Window> window;
    };

}