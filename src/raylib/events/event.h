//
// Created by ilias on 03/06/2021.
//

#ifndef BOMBERMAN_EVENT_H
#define BOMBERMAN_EVENT_H

#include "raylib.h"
#include <vector>

namespace RL {
    class Event {
    public:
        static bool isKeyDown(int key);

        static bool isKeyPressed(int key);

        static std::vector<KeyboardKey> &getKeysPressed(bool getRef = true);

        static bool isMouseClicked();
    };
}

#endif //BOMBERMAN_EVENT_H
