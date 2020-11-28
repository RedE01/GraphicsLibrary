#pragma once

namespace rgl {

    struct Vector2i {
        Vector2i() : x(0), y(0) {}
        Vector2i(const int& x, const int& y) : x(x), y(y) {}
        int x, y;
    };
    
}