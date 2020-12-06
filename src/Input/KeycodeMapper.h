#pragma once
#include "Keycodes.h"
#include <unordered_map>

namespace rgl {

    class KeycodeMapper {
    public:
        KeycodeMapper();

        int getKey(const int& keycode);

    private:
        std::unordered_map<int, int> m_keyMap;
    };
}