#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "main.h"
#include "raylib.h"
#include "msg.hpp"

namespace client {
    void debug(std::string f) { 
        if (BE_DEBUG) {
            // TODO: FIXME
            cout << "placeholder";
        }
    }
}

namespace Menu {
    class Button {
        public:
            int x;
            int y;
            int w;
            int h;
            Color c;
            Button(int _x, int _y, int _w, int _h, Color _c) {
                x = _x;
                y = _y;
                w = _w;
                h = _h;
                c = _c;
            }
    };
}

struct WindowInfo {
    uint8_t state = WIN_MENU;
    int height = 600;
    int width = 800;
    const char* title = "UFOPaper Scissors 0.2";
};

void DrawMenu(std::vector<Menu::Button> b);

#endif
