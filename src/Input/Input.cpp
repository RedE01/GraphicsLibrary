#include "Input.h"
#include "../Event/InputEvent.h"
#include <cstring>

namespace rgl {

    bool Input::m_keys[KEY_LAST] = { false };
    bool Input::m_keysPrev[KEY_LAST] = { false };

    bool Input::GetKeyDown(const int& keycode) {
        if(keycode < 0 || keycode >= KEY_LAST) return false;
        return m_keys[keycode] && !m_keysPrev[keycode];
    }

    bool Input::GetKey(const int& keycode) {
        if(keycode < 0 || keycode >= KEY_LAST) return false;
        return m_keys[keycode];
    }

    bool Input::GetKeyUp(const int& keycode) {
        if(keycode < 0 || keycode >= KEY_LAST) return false;
        return !m_keys[keycode] && m_keysPrev[keycode];
    }

    void Input::Update() {
        std::memcpy(m_keysPrev, m_keys, KEY_LAST);
    }

    void Input::HandleEvent(Event* e) {
        if(!e->isInCategory(EventCategory::EventCategoryInput)) return;

        if(e->isInCategory(EventCategory::EventCategoryKeyboard)) {
            if(e->GetEventType() == EventType::KeyPressed) {
                setKey(((KeyPressedEvent*)e)->key, true);
            }
            if(e->GetEventType() == EventType::KeyReleased) {
                setKey(((KeyReleasedEvent*)e)->key, false);
            }
        }
    }

    void Input::setKey(const int& keycode, const bool& val) {
        if(keycode < 0 || keycode >= KEY_LAST) return;
        m_keys[keycode] = val;
    }

}