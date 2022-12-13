//
// Created by ilias on 03/06/2021.
//

#include "raylib.h"
#include "window.h"

RL::Window::Window(int width, int height, const std::string &name, int fps) {
    InitWindow(width, height, name.c_str());
    SetTargetFPS(fps);
    if (!IsWindowReady()) {
        throw(err::Core("Can't create window"));
    }
    this->width = width;
    this->heigth = height;
    this->shouldClose = false;
}

RL::Window::~Window() {
    CloseWindow();
}

void RL::Window::setCursorState(bool state) {
    if (state)
        ShowCursor();
    else HideCursor();
}

bool RL::Window::isMouseInRange(float rec_top_left_x, float rec_top_left_y, float width, float height) {
    static Vector2 mousePoint = { 0.0f, 0.0f };
    mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, Rectangle{rec_top_left_x, rec_top_left_y, width, height});
}

bool RL::Window::isOpen() {
    return !WindowShouldClose();
}

void RL::Window::setShouldClose(bool close) {
    this->shouldClose = close;
}

const bool &RL::Window::getShouldClose() const {
    return this->shouldClose;
}