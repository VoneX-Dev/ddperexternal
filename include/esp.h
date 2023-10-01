#pragma once
#include <imgui/imgui.h>

class ESP{
    public:
        bool enabled = false;
        bool show_nearest = true;

        ImColor color_box = ImColor(255, 255, 255, 255);
        ImColor color_name = ImColor(255, 255, 255, 255);
        ImColor color_line = ImColor(255, 255, 255, 255);
};