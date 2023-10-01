#include <player.h>
#include <vector2.h>
#include <memory.h>
#include <offsets.h>
#pragma once

class LocalPlayer : public Player
{
    public:
        Vector2 aim;
        Vector2 aimWorld;

        LocalPlayer(uintptr_t localPlayer, const Memory *memory){
            this->localPlayer = localPlayer;
            this->players_address = players_address;
            this->memory = memory;
        }

        LocalPlayer(){};

        void updateLocalPlayerData(Player player);

    private:
        uintptr_t localPlayer;
        uintptr_t players_address;
        const Memory *memory;

};