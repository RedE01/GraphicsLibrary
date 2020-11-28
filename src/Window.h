#pragma once
#include "Etc/Vector.h"

#include <memory>

namespace rgl {

    class Window {
    protected:
        Window(const char* title, Vector2i pos, Vector2i size);

    public:
        virtual void open() = 0;
        static std::unique_ptr<Window> Create(const char* title, Vector2i pos, Vector2i size);

    public:
        Vector2i pos, size;
    };

}