#pragma once
#include <cstddef>

class Offsets {
    public:
        static constexpr ptrdiff_t static_server = 0x0033DD18;
        static constexpr ptrdiff_t online_players = 0x142C;
        static constexpr ptrdiff_t localplayer_id = 0x1428;
        static constexpr ptrdiff_t first_player = 0x1450;
        static constexpr ptrdiff_t next_player = 0xF8;
        static constexpr ptrdiff_t position = 0x153C;
        static constexpr ptrdiff_t gametick = 0x1530; //game stick nist to in client kiri?
        static constexpr ptrdiff_t freezed = 0x1508;
        
        static constexpr ptrdiff_t static_localplayer = 0x002F2D38;
        static constexpr ptrdiff_t my_aim = 0x10; 
        static constexpr ptrdiff_t my_aim_world = 0x20;
    

};