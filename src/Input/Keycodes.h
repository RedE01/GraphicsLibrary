#pragma once

namespace rgl {

    enum Key {
        NO_KEY = 0,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        Esc, Tab, CapsLock, Space, LeftShift, LeftControl, RightShift, RightControl, LeftAlt, RightAlt, Enter, Backspace,
        Insert, Home, PageUp, Delete, End, PageDown,
        Left, Up, Right, Down,
        KEY_LAST
    };
    
    enum MouseButton {
        NO_BUTTON = 0,
        LEFT, MIDDLE, RIGHT
    };

}