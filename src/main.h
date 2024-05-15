#pragma once
#include "imgui_internal.h"
#include <Windows.h>
void CustomStyleColor() // Отрисовка цветов
{
    ImGuiStyle& s = ImGui::GetStyle();
    ImGuiContext& g = *GImGui;

    s.Colors[ImGuiCol_WindowBg] = ImColor(9, 10, 10, 244);
    s.Colors[ImGuiCol_ChildBg] = ImColor(16, 15, 15, 255);
    //    s.Colors[ImGuiCol_ChildBg] = ImColor(165, 175, 185, 0);
    s.Colors[ImGuiCol_PopupBg] = ImColor(16, 15, 15, 127);
    s.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
    s.Colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, 255);
    //    s.Colors[ImGuiCol_FrameBg] = ImColor(11, 11, 16, 160);
    s.Colors[ImGuiCol_Border] = ImColor(14, 13, 19, 0);
    s.Colors[ImGuiCol_TextSelectedBg] = ImColor(35, 32, 43, 160);
    s.Colors[ImGuiCol_MenuBarBg] = ImColor(9, 10, 10, 244);

    s.ChildRounding = 4.f;
    s.WindowRounding = 7.f;
}

HWND hwnd;
RECT rc;
float WIDTH = 700;
float HEIGHT = 500; 

ImVec2 menu_size = { WIDTH, HEIGHT };

#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
static float color[4] = { 115/255.f, 210/255.f, 254/255.f, 1.f };
static float color1[4] = { 15 / 255.f, 210 / 255.f, 154 / 255.f, 1.f };
static float color2[4] = { 57 / 255.f, 19 / 255.f, 128 / 255.f, 1.f };
ImFont* Main_Font = nullptr;
ImFont* Lexend_Bold_Font = nullptr;
ImFont* Ico_Font = nullptr;
ImFont* Ico_Color = nullptr;
ImFont* Lexend_Font = nullptr;
int tabs = 0, sub_tabs = 0;
ImColor color_edit4 = { 0 / 255.f, 255 / 255.f, 208 / 255.f, 1.f };
static char textput1[64] = "";
IDirect3DTexture9* Logotip = nullptr;
IDirect3DTexture9* User = nullptr;
float tab_anim = 0.f;
