#pragma once

#include "imgui.h"

namespace c {

    namespace other
    {
        inline ImVec4 white_color = ImColor(255, 255, 255, 255);
        inline ImVec4 low_color = ImColor(255, 255, 255, 0);
        inline ImVec4 accent_color = ImColor(115, 210, 254, 255);
        inline ImVec4 background_color = ImColor(100, 100, 100, 255);

        inline ImVec4 tab_button = ImColor(37, 37, 37, 255);
        inline ImVec4 ico_tab_button = ImColor(115, 210, 254, 255);

        inline ImVec4 backgroud = ImColor(16, 15, 15, 255);
        inline ImVec4 line = ImColor(40, 40, 40, 255);
        inline ImVec4 line_tab = ImColor(6, 207, 169, 255);
        inline ImVec4 text = ImColor(255, 255, 255, 140);
    }

    inline ImVec4 accent_color = ImColor(0, 255, 208, 255);
    inline ImVec4 accent_color_inact = ImColor(255, 0, 76, 255);

    namespace bg
    {
        inline ImVec4 background = ImColor(27, 28, 34, 140);
        inline ImVec2 size = ImVec2(60, 590);
        inline float rounding = 10.f;
    }

    namespace child
    {
        inline ImVec4 background = ImColor(35, 35, 35, 255);
        inline ImVec4 background_line = ImColor(115, 210, 254, 255);
        inline ImVec4 text = ImColor(255, 255, 255, 255);
        inline ImVec4 background_rect = ImColor(115, 210, 254, 255);
        inline ImVec4 background_rect1 = ImColor(115, 210, 254, 0);
        inline ImVec4 ico_child = ImColor(124, 213, 255, 255);
        inline float rounding = 6.f;
    }

    namespace checkbox
    {
        inline ImVec4 background_active = ImColor(0, 255, 208, 80);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);
        inline ImVec4 color_background_active = ImColor(0, 255, 208, 80);
        inline ImVec4 color_background_inactive = ImColor(255, 0, 76, 80);
        inline ImVec4 circle_active = ImColor(255, 255, 255, 255);
        inline ImVec4 circle_inactive = ImColor(255, 0, 76, 255);
        inline ImVec4 circle_outline = ImColor(42, 45, 51, 255);

        inline ImVec4 circle_shadow_activ = ImColor(0, 255, 208, 255);
        inline ImVec4 circle_shadow_inactiv = ImColor(255, 0, 76, 255);
        inline float rounding = 30.f;
    }

    namespace slider
    {
        inline ImVec4 background_active = ImColor(115, 210, 254, 255);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 0);
        inline ImVec4 circle_active = ImColor(255, 255, 255, 255);
    }

    namespace tab
    {
        inline ImVec4 image_inactive = ImColor(104, 114, 129, 255);
        inline ImVec4 line_inactive = ImColor(104, 114, 129, 0);
        inline ImVec4 circle_user = ImColor(114, 19, 42, 200);

        inline ImVec4 text_active = ImColor(200, 200, 200, 200);
        inline ImVec4 text_hov = ImColor(200, 200, 200, 200);
        inline ImVec4 text = ImColor(200, 200, 200, 200);


    }

    namespace combo
    {
        inline ImVec4 background_inactive = ImColor(26, 26, 26, 255);

        inline float rounding = 3.f;
    }

    namespace keybind
    {
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);

        inline float rounding = 2.f;
    }

  

    namespace button
    {
        inline ImVec4 background_active = ImColor(115, 210, 254, 255);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);

        inline float rounding = 2.f;
    }

    namespace input
    {
        inline ImVec4 background_active = ImColor(38, 43, 50, 255);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);

        inline float rounding = 2.f;
    }

    namespace text
    {
        inline ImVec4 text_black = ImColor(0, 0, 0, 255);

        inline ImVec4 text_active = ImColor(255, 255, 255, 255);
        inline ImVec4 text_hov = ImColor(64, 64, 64, 255);
        inline ImVec4 text = ImColor(64, 64, 64, 255);
        inline ImVec4 text_ico = ImColor(115, 210, 254, 255);
        inline ImVec4 text_hide = ImColor(255, 255, 255, 0);
    }


    namespace picker {

        inline ImVec4 background = ImColor(20, 20, 20, 255);

        inline ImVec4 shadow = ImColor(8, 8, 8, 255);
        inline ImVec4 border = ImColor(5, 5, 5, 255);

        inline ImVec4 text_active = ImColor(140, 141, 145, 255);
        inline ImVec4 text_hov = ImColor(75, 75, 77, 255);
        inline ImVec4 text = ImColor(65, 65, 67, 255);

    }


}
