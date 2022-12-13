//
// Created by ilias on 03/06/2021.
//

#include <vector>
#include "raylib.h"
#include "event.h"

bool RL::Event::isKeyDown(int key) {
    return IsKeyDown(key);
}

bool RL::Event::isKeyPressed(int key) {
    return IsKeyPressed(key);
}

//Put all keys used
std::vector<KeyboardKey> &RL::Event::getKeysPressed(bool update)
{
    static std::vector<KeyboardKey> keys = {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_E, KEY_S, KEY_D, KEY_F, KEY_SPACE, KEY_ENTER, KEY_G, KEY_V, KEY_B, KEY_N, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_O};
    static std::vector<KeyboardKey> keysPressed;

    if (!update)
        return keysPressed;
    for (auto &key : keys) {
        if (IsKeyDown(key))
            keysPressed.push_back(key);
    }
    if (keysPressed.empty())
        keysPressed.push_back(KEY_NULL);

    return keysPressed;
}

bool RL::Event::isMouseClicked() {
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}
