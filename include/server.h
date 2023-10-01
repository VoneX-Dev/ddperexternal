#include <memory.h>
#include <player.h>
#include <localplayer.h>
#include <offsets.h>
#pragma once

class Server{
    public:
        int online_players;
        static const int MAX_PLAYERS = 63 + 1;
        Player players[MAX_PLAYERS];
        LocalPlayer localPlayer;

        Server(uintptr_t players_address, uintptr_t localPlayer_address, const Memory *memory){
            this->players_address = players_address;
            this->memory = memory;
            localPlayer = LocalPlayer(localPlayer_address, memory);
        }

        void updateServerData();
        static bool GetValidPlayer(Player player);

    private:
        uintptr_t players_address;
        const Memory *memory;
};