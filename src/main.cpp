#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <Windows.h>
#include <memory>
#include <kthook/kthook.hpp>
#include "main.h"
#include "Image.h"
#include "imgui_settings.h"
#include "Font.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

namespace image
{
    IDirect3DTexture9* bg = nullptr;
    IDirect3DTexture9* bg_blurred = nullptr;
    IDirect3DTexture9* bg_decore = nullptr;

    IDirect3DTexture9* logo = nullptr;
    IDirect3DTexture9* logo_cheat = nullptr;

    IDirect3DTexture9* arrow = nullptr;

    IDirect3DTexture9* crosshair = nullptr;
    IDirect3DTexture9* user = nullptr;
    IDirect3DTexture9* eye = nullptr;
    IDirect3DTexture9* save = nullptr;
    IDirect3DTexture9* settings = nullptr;

    IDirect3DTexture9* tab_crosshair = nullptr;
    IDirect3DTexture9* tab_user = nullptr;
    IDirect3DTexture9* tab_eye = nullptr;
    IDirect3DTexture9* tab_save = nullptr;
    IDirect3DTexture9* tab_settings = nullptr;
    IDirect3DTexture9* tab_search = nullptr;
    IDirect3DTexture9* ico_begin = nullptr;
    IDirect3DTexture9* ico_begin_1 = nullptr;
    IDirect3DTexture9* ico_begin_2 = nullptr;
}

using CTimer__UpdateSignature = void(__cdecl*)();
using PresentSignature = HRESULT(__stdcall*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
using ResetSignature = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
using WndProcSignature = HRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM);

kthook::kthook_simple<CTimer__UpdateSignature> CTimerHook{};
kthook::kthook_signal<PresentSignature> PresentHook{};
kthook::kthook_signal<ResetSignature> ResetHook{};
kthook::kthook_simple<WndProcSignature> WndProcHook{};

bool ImGuiEnable{};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT WndProc(const decltype(WndProcHook)& hook, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_KEYUP) {
        if (wParam == VK_F9)
            ImGuiEnable = { !ImGuiEnable };
    }

    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam)) {
        return 1;
    }
    return hook.get_trampoline()(hwnd, uMsg, wParam, lParam);
}

std::optional<HRESULT> D3D9Present(const decltype(PresentHook)& hook, IDirect3DDevice9* pDevice, CONST RECT* pSrcRect, CONST RECT* pDestRect, HWND hDestWindow, CONST RGNDATA* pDirtyRegion) {
    static bool ImGuiInit{};
    if (!ImGuiInit) {
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(**reinterpret_cast<HWND**>(0xC17054));
        ImGui_ImplDX9_Init(pDevice);
        ImGuiIO io = ImGui::GetIO();
        io.IniFilename = nullptr; 
        

        Main_Font = io.Fonts->AddFontFromMemoryTTF(&Lexend, sizeof Lexend, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

        Lexend_Bold_Font = io.Fonts->AddFontFromMemoryTTF(&Lexend_Bold, sizeof Lexend_Bold, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

        if (image::bg == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, background, sizeof(background), &image::bg);
        if (image::crosshair == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, user_crosshair, sizeof(user_crosshair), &image::crosshair);
        if (image::user == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, user_user, sizeof(user_user), &image::user);
        if (image::eye == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, user_eye, sizeof(user_eye), &image::eye);
        if (image::save == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, user_save, sizeof(user_save), &image::save);
        if (image::settings == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, user_settings, sizeof(user_settings), &image::settings);
        if (image::tab_crosshair == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, tab_user_crosshair, sizeof(tab_user_crosshair), &image::tab_crosshair);
        if (image::tab_user == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, tab_user_user, sizeof(tab_user_user), &image::tab_user);
        if (image::tab_eye == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, tab_user_eye, sizeof(tab_user_eye), &image::tab_eye);
        if (image::tab_save == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, tab_user_save, sizeof(tab_user_save), &image::tab_save);
        if (image::tab_settings == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, tab_user_settings, sizeof(tab_user_settings), &image::tab_settings);
        if (image::tab_search == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, tab_user_search, sizeof(tab_user_search), &image::tab_search);
        if (image::ico_begin == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, begin_ico, sizeof(begin_ico), &image::ico_begin);
        if (image::ico_begin_1 == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, begin_ico_1, sizeof(begin_ico_1), &image::ico_begin_1);
        if (image::ico_begin_2 == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, begin_ico_2, sizeof(begin_ico_2), &image::ico_begin_2);
        if (image::arrow == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, icon_arrow, sizeof(icon_arrow), &image::arrow);

        auto latest_wndproc_ptr = GetWindowLongPtrW(**reinterpret_cast<HWND**>(0xC17054), GWLP_WNDPROC);
        WndProcHook.set_dest(latest_wndproc_ptr);
        WndProcHook.set_cb(&WndProc);
        WndProcHook.install();

        ImGuiInit = { true };
    }

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
        
    ImGui::GetStyle().ItemSpacing = ImVec2(0, 10);

    CustomStyleColor();

    ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_FirstUseEver);
    ImGui::Begin("IMGUI", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);
    {
        const auto& p = ImGui::GetWindowPos();
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 7, p.y + 10), ImVec2(p.x + 123, p.y + 490), ImGui::GetColorU32(c::other::backgroud),14, ImDrawFlags_RoundCornersLeft);

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 130 , p.y + 10), ImVec2(p.x + 692, p.y + 60), ImGui::GetColorU32(c::other::backgroud), 3);

        if (Logotip == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, Logo, sizeof(Logo), &Logotip); 
        ImGui::GetForegroundDrawList()->AddImageRounded(Logotip, ImVec2(p.x + 35, p.y + 26), ImVec2(p.x + 95, p.y + 88), ImVec2(0, 0), ImVec2(1, 1), ImColor(47, 189, 255, 255) /*color*/, 0 /*rounding*/);

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 18, p.y + 104), ImVec2(p.x + 113, p.y + 105),ImColor(91,200,251), 0);
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 18, p.y + 396), ImVec2(p.x + 113, p.y + 397), ImColor(91, 200, 251), 0);
        ImGui::GetWindowDrawList()->AddCircle(ImVec2(p.x + 65, p.y + 443), 25.f, ImColor(47, 189, 255));
        if (User == nullptr) D3DXCreateTextureFromFileInMemory(pDevice, Logo_User, sizeof(Logo_User), &User); 
        ImGui::GetForegroundDrawList()->AddImageRounded(User, ImVec2(p.x + 41, p.y + 419), ImVec2(p.x + 89, p.y + 467), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255) /*color*/, 100 /*rounding*/);
        ImGui::SetCursorPos(ImVec2(652, 21));
        ImGui::TabIco("search", image::tab_search, ImVec2(30, 30));

        static int page = 0;

        static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

        tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (page == active_tab ? 1.f : -1.f)), 0.f, 1.f);
        tab_add = ImClamp(tab_add + (std::round(350.f) * ImGui::GetIO().DeltaTime * (page == active_tab ? 1.f : -1.f)), 0.f, 1.f);

        if (tab_alpha == 0.f && tab_add == 0.f) active_tab = page;

        ImGui::BeginGroup();
        {
            ImGui::SetCursorPos(ImVec2(50, 135));
            if (ImGui::Tab(1, 0 == page, image::crosshair, ImVec2(30, 30))) page = 0;
            ImGui::SetCursorPos(ImVec2(50, 185));
            if (ImGui::Tab(2, 1 == page, image::user, ImVec2(30, 30))) page = 1;
            ImGui::SetCursorPos(ImVec2(50, 235));
            if (ImGui::Tab(3, 2 == page, image::eye, ImVec2(30, 30))) page = 2;
            ImGui::SetCursorPos(ImVec2(50, 285));
            if (ImGui::Tab(4, 3 == page, image::save, ImVec2(30, 30))) page = 3;
            ImGui::SetCursorPos(ImVec2(50, 335));
            if (ImGui::Tab(5, 4 == page, image::settings, ImVec2(30, 30))) page = 4;

        }ImGui::EndGroup();

        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style.Alpha);            

        if (active_tab == 0)
        {
            ImGui::SetCursorPos(ImVec2(140, 21));
            ImGui::TabButton("crosshair", image::tab_crosshair, ImVec2(31, 31));

            ImGui::GetForegroundDrawList()->AddText(Lexend_Bold_Font, 17.f, ImVec2(179 + p.x, 29 + p.y), ImGui::GetColorU32(c::other::text), "RAGEBOT");

            ImGui::SetCursorPos(ImVec2(130, 68));
            ImGui::BeginChild("General", image::ico_begin, ImVec2(277, 422));
            {
                ImGui::SetCursorPos(ImVec2(11, 68));
                ImGui::BeginGroup();
                {
                    static bool enable_aim = false;
                    ImGui::Checkbox("Aimbot", &enable_aim);
                    static int slider_int = 0;
                    ImGui::SliderInt("Hp Value", &slider_int, 1, 100, "%d%");
                    static bool AutoShot = false;
                    ImGui::Checkbox("AutoShot", &AutoShot);
                    static int select = 0;     
                    const char* items[3]{ "One", "Two", "Three" };
                    ImGui::Combo("Combo", &select, items, IM_ARRAYSIZE(items), 3);
                    static bool Triggerbot = false;
                    ImGui::Checkbox("Triggerbot", &Triggerbot);
                    static bool SpeedHack = false;
                    ImGui::Checkbox("SpeedHack", &SpeedHack);
                    static bool Fly = false;   
                    ImGui::Checkbox("Fly", &Fly);
                    static int KeyBind = 0;
                    ImGui::Keybind("KeyBind", &KeyBind);

                }ImGui::EndGroup();

            }ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(414, 68));
            ImGui::BeginChild("Misc", image::ico_begin_1, ImVec2(277, 193));
            {
                ImGui::SetCursorPos(ImVec2(11, 68));
                ImGui::BeginGroup();
                {
                    static bool WallHack = false;
                    ImGui::CheckPicker("WallHack", "##IDK Color", &WallHack, (float*)&color);
                    static bool Esp = false;
                    ImGui::CheckPicker("Esp Health", "##IDK1 Color", &Esp, (float*)&color1);
                    static bool Weapon = false;
                    ImGui::CheckPicker("Esp Weapon", "##IDK2 Color", &Weapon, (float*)&color2);

                }ImGui::EndGroup();

            }ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(415, 268));
            ImGui::BeginChild("Upload", image::ico_begin_2, ImVec2(277, 193));
            {
                ImGui::SetCursorPos(ImVec2(11, 68));
                ImGui::BeginGroup();
                {
                    ImGui::Button("Teleport", ImVec2(255, 25));

                }ImGui::EndGroup();

            }ImGui::EndChild();
        }
        ImGui::PopStyleVar();
    }ImGui::End();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    return std::nullopt;
}

std::optional<HRESULT> D3D9Lost(const decltype(ResetHook)& hook, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentParams) {
    ImGui_ImplDX9_InvalidateDeviceObjects();
    return std::nullopt;
}

void D3D9Reset(const decltype(ResetHook)& hook, HRESULT& return_value, IDirect3DDevice9* device_ptr, D3DPRESENT_PARAMETERS* parameters) {
    ImGui_ImplDX9_InvalidateDeviceObjects();
}

void setD3D9Hooks() {
    DWORD pDevice = *reinterpret_cast<DWORD*>(0xC97C28);
    void** vTable = *reinterpret_cast<void***>(pDevice);

    PresentHook.set_dest(vTable[17]);
    PresentHook.before.connect(&D3D9Present);
    PresentHook.install();

    ResetHook.set_dest(vTable[16]);
    ResetHook.before.connect(&D3D9Lost);
    ResetHook.after.connect(&D3D9Reset);
    ResetHook.install();
}

void CTimer__Update(const decltype(CTimerHook)& hook) {
    static bool init{};
    if (!init) {
        setD3D9Hooks();
        init = { true };
    }

    hook.get_trampoline()();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CTimerHook.set_dest(0x561B10);
        CTimerHook.set_cb(&CTimer__Update);
        CTimerHook.install();
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}