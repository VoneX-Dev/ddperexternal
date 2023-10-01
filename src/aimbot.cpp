#include <aimbot.h>

void Aimbot::aimTarget(Vector2 target, LocalPlayer *localPlayer){
    target.x = target.x - localPlayer->position.x;
    target.y = target.y - localPlayer->position.y;
    memory->Write<Vector2>(localPlayer_address + Offsets::my_aim, target);
}

float Aimbot::distance(Vector2 a, Vector2 b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); // kiri++
}

Player Aimbot::GetNearestInSector(double a, int r, Server *server)
{
    a = a * (M_PI / 180);

    double closestDist = 1.79769;
    Player closestPlayer = Player();

    float aAim = atan2(server->localPlayer.aim.y, server->localPlayer.aim.x);

    for (int i = 0; i < Server::MAX_PLAYERS; i++)
    {
        Player player = server->players[i];

        float dist = Aimbot::distance(player.position, server->localPlayer.position);

        if (Server::GetValidPlayer(player) && player.id != server->localPlayer.id && dist < r)
        {

            float aPlayer = atan2(player.position.y - server->localPlayer.position.y, player.position.x - server->localPlayer.position.x);

            if (aPlayer > aAim - (a / 2) && aPlayer < aAim + (a / 2))
            {
                
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closestPlayer = player;
                }
            }
        }
    }

    nearestPlayer = closestPlayer;

    return closestPlayer;
}

Player Aimbot::GetNearestToPlayer(float maxDistance, Server *server)
{

    float closestDist = maxDistance;
    Player closestPlayer;

    for (int i = 0; i < Server::MAX_PLAYERS; i++)
    {
        Player player = server->players[i];

        if (player.id != server->localPlayer.id && server->GetValidPlayer(player) && ((avoid_freezed_tee && !player.freezed) || !avoid_freezed_tee))
        {
            float dist = Aimbot::distance(player.position, server->localPlayer.position);

            if (dist > 0 && dist < closestDist)
            {
                closestDist = dist;
                closestPlayer = player;
            }
            
        }
    }

    nearestPlayer = closestPlayer;

    return closestPlayer;
}
