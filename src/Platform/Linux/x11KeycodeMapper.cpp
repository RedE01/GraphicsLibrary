#include "../../Input/KeycodeMapper.h"
#include <X11/keysym.h>
#include <X11/X.h>

namespace rgl {

    KeycodeMapper::KeycodeMapper() {
        m_keyMap[XK_a] = Key::A; m_keyMap[XK_b] = Key::B; m_keyMap[XK_c] = Key::C; m_keyMap[XK_d] = Key::D;
        m_keyMap[XK_e] = Key::E; m_keyMap[XK_f] = Key::F; m_keyMap[XK_g] = Key::G; m_keyMap[XK_h] = Key::H;
        m_keyMap[XK_i] = Key::I; m_keyMap[XK_j] = Key::J; m_keyMap[XK_k] = Key::K; m_keyMap[XK_l] = Key::L;
        m_keyMap[XK_m] = Key::M; m_keyMap[XK_n] = Key::N; m_keyMap[XK_o] = Key::O; m_keyMap[XK_p] = Key::P;
        m_keyMap[XK_q] = Key::Q; m_keyMap[XK_r] = Key::R; m_keyMap[XK_s] = Key::S; m_keyMap[XK_t] = Key::T;
        m_keyMap[XK_u] = Key::U; m_keyMap[XK_v] = Key::V; m_keyMap[XK_w] = Key::W; m_keyMap[XK_x] = Key::X;
        m_keyMap[XK_y] = Key::Y; m_keyMap[XK_z] = Key::Z;

        m_keyMap[XK_0] = Key::K0; m_keyMap[XK_1] = Key::K1; m_keyMap[XK_2] = Key::K2; m_keyMap[XK_3] = Key::K3;
        m_keyMap[XK_4] = Key::K4; m_keyMap[XK_5] = Key::K5; m_keyMap[XK_6] = Key::K6; m_keyMap[XK_7] = Key::K7;
        m_keyMap[XK_8] = Key::K8; m_keyMap[XK_9] = Key::K9;

        m_keyMap[XK_F1] = Key::F1; m_keyMap[XK_F2]  = Key::F2;  m_keyMap[XK_F3]  = Key::F3;  m_keyMap[XK_F4]  = Key::F4;
        m_keyMap[XK_F5] = Key::F5; m_keyMap[XK_F6]  = Key::F6;  m_keyMap[XK_F7]  = Key::F7;  m_keyMap[XK_F8]  = Key::F8;
        m_keyMap[XK_F9] = Key::F9; m_keyMap[XK_F10] = Key::F10; m_keyMap[XK_F11] = Key::F11; m_keyMap[XK_F12] = Key::F12;

        m_keyMap[XK_Escape] = Key::Esc; m_keyMap[XK_Tab] = Key::Tab; m_keyMap[XK_Caps_Lock] = Key::CapsLock; m_keyMap[XK_space] = Key::Space;
        m_keyMap[XK_Shift_L] = Key::LeftShift; m_keyMap[XK_Control_L] = Key::LeftControl; m_keyMap[XK_Shift_R] = Key::RightShift; m_keyMap[XK_Control_R] = Key::RightControl;
        m_keyMap[XK_Alt_L] = Key::LeftAlt; m_keyMap[XK_Alt_R] = Key::RightAlt; m_keyMap[XK_Return] = Key::Enter; m_keyMap[XK_BackSpace] = Key::Backspace,

        m_keyMap[XK_Insert] = Key::Insert; m_keyMap[XK_Home] = Key::Home; m_keyMap[XK_Page_Up] = Key::PageUp; m_keyMap[XK_Delete] = Key::Delete;
        m_keyMap[XK_End] = Key::End; m_keyMap[XK_Page_Down] = Key::PageDown;

        m_keyMap[XK_Left] = Key::Left; m_keyMap[XK_Up] = Key::Up; m_keyMap[XK_Right] = Key::Right; m_keyMap[XK_Down] = Key::Down;


        m_buttonMap[Button1] = MouseButton::LEFT; m_buttonMap[Button2] = MouseButton::MIDDLE; m_buttonMap[Button3] = MouseButton::RIGHT;
    }

    int KeycodeMapper::getKey(const int& keycode) {
        auto keySearch = m_keyMap.find(keycode);
        if(keySearch == m_keyMap.end()) return 0;
        return keySearch->second;
    }

    int KeycodeMapper::getButton(const int& button) {
        auto buttonSearch = m_buttonMap.find(button);
        if(buttonSearch == m_buttonMap.end()) return button;
        return buttonSearch->second;
    }

}