//
// Created by ilias on 03/06/2021.
//

#ifndef BOMBERMAN_WINDOW_H
#define BOMBERMAN_WINDOW_H

#include <string>
#include "game.h"
#include "../../errors/Error.h"
namespace RL {
    class Window {
    public:
        Window(int width, int height, const std::string &name, int fps = 60);

        ~Window();

    public:
        static void setCursorState(bool state);

        static bool
        isMouseInRange(float rec_top_left_x, float rec_top_left_y, float width,
                       float height);

        static bool isOpen();

    public:
        void setShouldClose(bool close);

        const bool &getShouldClose() const;

    private:
        int width;
        int heigth;
        bool shouldClose;
    };
}

#endif //BOMBERMAN_WINDOW_H
