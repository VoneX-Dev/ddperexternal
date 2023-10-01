#include <server.h>

void Server::updateServerData(){

    this->online_players = memory->Read<int32_t>(players_address + Offsets::online_players);

    if(this->online_players > 1){
        for(int i = 0; i < Server::MAX_PLAYERS; i++){
            const uintptr_t player = players_address + (Offsets::next_player * i);
            this->players[i].id = i;
            this->players[i].position = memory->Read<Vector2>(player + Offsets::position);
            this->players[i].gametick = memory->Read<int32_t>(player + Offsets::gametick);
            int freezed = memory->Read<int32_t>(player + Offsets::freezed);
            this->players[i].freezed = freezed > 0 ? true : false;
            
            if(i == memory->Read<int32_t>(players_address + Offsets::localplayer_id)){
                this->localPlayer.updateLocalPlayerData(this->players[i]);
            }
        }
    }

}

bool Server::GetValidPlayer(Player player){
    // return player.gametick != 0 && player.id != this->localPlayer.id && (player.id > 0 || player.id < Server::MAX_PLAYERS);
    return player.position.x != 0 && player.position.y != 0;
}