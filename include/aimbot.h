#include <memory.h>
#include <offsets.h>
#pragma once

#include <vector2.h>
#include <localplayer.h>
#include <cmath>
#include <server.h>

class Aimbot{
    public:
        bool global_fov_enabled = false;
        bool focused_fov_enabled = false;
        bool silent_enabled = false;
        bool avoid_freezed_tee = true;
        int fov_distance = 400;
        float fov_angle = 90;

        Player nearestPlayer = Player();

        Aimbot(uintptr_t localPlayer_address, const Memory *memory){
            this->localPlayer_address = localPlayer_address;
            this->memory = memory;
        }
        void aimTarget(Vector2 target, LocalPlayer *localPlayer);
        Player GetNearestInSector(double a, int r, Server *server);
        Player GetNearestToPlayer(float maxDistance, Server *server);

        static float distance(Vector2 a, Vector2 b);

    private:
        uintptr_t localPlayer_address;
        const Memory *memory;
};