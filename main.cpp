#include <iostream>
#include "include/aimbot.h"
#include <server.h>
// #include <gui.h>
#include <signature.hpp>
#include <ui.h>
#include "include/esp.h"
#include <iostream>
#include <chrono>
#include <thread>
bool isRunning(LPCWSTR pName)
{
    HWND hwnd;
    hwnd = FindWindowW(NULL, pName);
    if (hwnd != 0) {
        return true;
    }
    else {
        return false;
    }
}
int main(int, char**) {
    const char* narrowName = "DDPER Client";
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, narrowName, -1, NULL, 0);
    if (bufferSize == 0) {
        // Handle conversion error
        return 1;
    }

    std::wstring wideName(bufferSize, 0);
    if (MultiByteToWideChar(CP_UTF8, 0, narrowName, -1, &wideName[0], bufferSize) == 0) {
        // Handle conversion error
        return 1;
    }

    if (!isRunning(wideName.c_str())) {
        std::cout << "DDPER is not running!" << std::endl;
        return 0;
    }
    // Rest of your code
}

    // signature test("DDPER.exe");
    // std::cout << std::hex << test.scan("e8 ? ? ? ? 90 8b cb") << std::endl;

    ui::CreateHUIWindow();
    ui::CreateUIDevice();
    ui::CreateUIImGui();

    char moduleName[10];
    strcpy(moduleName, "DDPER.exe");

    const auto memory = Memory(moduleName);
    const auto baseAddress = memory.GetModuleAddress(moduleName);

    const auto& players_address = memory.Read<uintptr_t>(baseAddress + Offsets::static_server);
    const auto& localPlayer_address = memory.Read<uintptr_t>(baseAddress + Offsets::static_localplayer);

    Server server(players_address, localPlayer_address, &memory);
    Aimbot aimbot(localPlayer_address, &memory);
    LocalPlayer localPlayer = LocalPlayer();
    ESP esp = ESP();

    while(ui::isRunning){

        if(GetAsyncKeyState(VK_F3)){
            aimbot.global_fov_enabled = true;
            std::cout << "Aimbot enabled" << std::endl;
        }else if(GetAsyncKeyState(VK_F4)){
            aimbot.global_fov_enabled = false;
            std::cout << "Aimbot disabled" << std::endl;
        }

        if(GetAsyncKeyState(VK_F6)){
            ui::isMenuOpen = true;
            ui::SetMenuOpen();
        }else if(GetAsyncKeyState(VK_F7)){
            ui::isMenuOpen = false;
            ui::SetMenuClose();
        }

        server.updateServerData();
        localPlayer = server.localPlayer;

        if(aimbot.global_fov_enabled || (aimbot.silent_enabled && GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_RBUTTON)) || aimbot.focused_fov_enabled){           
            Player player = aimbot.GetNearestToPlayer(aimbot.fov_distance, &server);
            if(aimbot.global_fov_enabled) 
                Player player = aimbot.GetNearestToPlayer(aimbot.fov_distance, &server);
            else if(aimbot.focused_fov_enabled)
                Player player = aimbot.GetNearestInSector(aimbot.fov_angle, aimbot.fov_distance, &server);

            if (Server::GetValidPlayer(player) && player.id != localPlayer.id && (player.id > 0 || player.id < Server::MAX_PLAYERS))
                aimbot.aimTarget(player.position, &localPlayer);
        
        }

        ui::BeginRenderUI();
        ui::RenderUI(&aimbot, &esp, &server);
        ui::EndRenderUI();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
            
    }

    ui::DestroyUIImGui();
    ui::DestroyUIDevice();
    ui::DestroyHUIWindow();
    return 0;
}
