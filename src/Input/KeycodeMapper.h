#pragma once
#include "Keycodes.h"
#include <unordered_map>

namespace rgl {

    class KeycodeMapper {
    public:
        KeycodeMapper();

        int getKey(const int& keycode);
        int getButton(const int& button);

    private:
        std::unordered_map<int, int> m_keyMap;
        std::unordered_map<int, int> m_buttonMap;
    };
}