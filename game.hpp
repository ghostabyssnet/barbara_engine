#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "main.hpp"

class Actor {
    Texture t;
    Vector2 pos;
};

class Map {
    std::vector<uint8_t> floor;
};

#endif
