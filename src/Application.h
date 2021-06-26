#pragma once
#include <memory>
#include "Window.h"
#include <limits>

namespace rgl {

    class Application {
    public:
        Application();

        void create(const char* title, Vector2i size, Vector2i pos = Vector2i(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
        void run();

        virtual void onUpdate() = 0;
        virtual void onEvent(Event* event) = 0;

    private:
        void handleEvent(Event* event);

    public:
        std::unique_ptr<Window> window;
    };

}