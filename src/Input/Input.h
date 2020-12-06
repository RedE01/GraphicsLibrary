#pragma one
#include "Keycodes.h"

namespace rgl {

    class Event;

    class Input {
    public:
        static bool GetKeyDown(const int& keycode);
        static bool GetKey(const int& keycode);
        static bool GetKeyUp(const int& keycode);

    private:
        Input() = delete;
        static void Update();
        static void HandleEvent(Event* e);
        static void setKey(const int& keycode, const bool& val);
        friend class Application;
        friend class Window;

    protected:
        static bool m_keys[KEY_LAST];
        static bool m_keysPrev[KEY_LAST];
    };

}