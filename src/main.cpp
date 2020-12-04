#include <iostream>
#include "Application.h"

class Test : public rgl::Application {
public:
    virtual void onUpdate() {
    }

    virtual void onEvent(rgl::Event* event) {
    }
};

int main() {
    Test t;
    t.create("test", rgl::Vector2i(0,0), rgl::Vector2i(720, 480));
    t.run();
}