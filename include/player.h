#include <vector2.h>
#pragma once

class Player{
    public:
        int id;
        Vector2 position;
        Vector2 speed;
        int gametick;
        float hook_time;
        bool freezed;
        int player_size = 64;

        Player(){}
};