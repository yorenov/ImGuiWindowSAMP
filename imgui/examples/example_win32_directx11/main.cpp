#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include "main.h"
#include "Image.h"
#include "imgui_settings.h"
#include "Font.h"
#include <codecvt>
#include <iomanip>
#include <dwmapi.h>
#include <D3DX11tex.h>

#pragma comment(lib, "D3DX11.lib")
// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace image
{
    ID3D11ShaderResourceView* bg = nullptr;
    ID3D11ShaderResourceView* bg_blurred = nullptr;
    ID3D11ShaderResourceView* bg_decore = nullptr;

    ID3D11ShaderResourceView* logo = nullptr;
    ID3D11ShaderResourceView* logo_cheat = nullptr;

    ID3D11ShaderResourceView* arrow = nullptr;

    ID3D11ShaderResourceView* crosshair = nullptr;
    ID3D11ShaderResourceView* user = nullptr;
    ID3D11ShaderResourceView* eye = nullptr;
    ID3D11ShaderResourceView* save = nullptr;
    ID3D11ShaderResourceView* settings = nullptr;

    ID3D11ShaderResourceView* tab_crosshair = nullptr;
    ID3D11ShaderResourceView* tab_user = nullptr;
    ID3D11ShaderResourceView* tab_eye = nullptr;
    ID3D11ShaderResourceView* tab_save = nullptr;
    ID3D11ShaderResourceView* tab_settings = nullptr;
    ID3D11ShaderResourceView* tab_search = nullptr;
    ID3D11ShaderResourceView* ico_begin = nullptr;
    ID3D11ShaderResourceView* ico_begin_1 = nullptr;
    ID3D11ShaderResourceView* ico_begin_2 = nullptr;
}
// Main code
int main(int, char**)
{
    WNDCLASSEXW wc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = nullptr;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = L"ImGui";
    wc.lpszClassName = L"Example";
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);


    RegisterClassExW(&wc);
    hwnd = CreateWindowExW(NULL, wc.lpszClassName, L"Loader", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH, HEIGHT, 0, 0, 0, 0);

    SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);

    POINT mouse;
    rc = { 0 };
    GetWindowRect(hwnd, &rc);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
 
    ImGui::StyleColorsDark();
 
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    Main_Font = io.Fonts->AddFontFromMemoryTTF(&Lexend, sizeof Lexend, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    Lexend_Bold_Font = io.Fonts->AddFontFromMemoryTTF(&Lexend_Bold, sizeof Lexend_Bold, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 0.f);
    D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };

    if (image::bg == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, background, sizeof(background), &info, pump, &image::bg, 0);

    if (image::crosshair == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, user_crosshair, sizeof(user_crosshair), &info, pump, &image::crosshair, 0);
    if (image::user == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, user_user, sizeof(user_user), &info, pump, &image::user, 0);
    if (image::eye == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, user_eye, sizeof(user_eye), &info, pump, &image::eye, 0);
    if (image::save == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, user_save, sizeof(user_save), &info, pump, &image::save, 0);
    if (image::settings == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, user_settings, sizeof(user_settings), &info, pump, &image::settings, 0);

    if (image::tab_crosshair == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, tab_user_crosshair, sizeof(tab_user_crosshair), &info, pump, &image::tab_crosshair, 0);
    if (image::tab_user == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, tab_user_user, sizeof(tab_user_user), &info, pump, &image::tab_user, 0);
    if (image::tab_eye == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, tab_user_eye, sizeof(tab_user_eye), &info, pump, &image::tab_eye, 0);
    if (image::tab_save == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, tab_user_save, sizeof(tab_user_save), &info, pump, &image::tab_save, 0);
    if (image::tab_settings == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, tab_user_settings, sizeof(tab_user_settings), &info, pump, &image::tab_settings, 0);

    if (image::tab_search == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, tab_user_search, sizeof(tab_user_search), &info, pump, &image::tab_search, 0);

    if (image::ico_begin == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, begin_ico, sizeof(begin_ico), &info, pump, &image::ico_begin, 0);

    if (image::ico_begin_1 == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, begin_ico_1, sizeof(begin_ico_1), &info, pump, &image::ico_begin_1, 0);

    if (image::ico_begin_2 == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, begin_ico_2, sizeof(begin_ico_2), &info, pump, &image::ico_begin_2, 0);

    if (image::arrow == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, icon_arrow, sizeof(icon_arrow), &info, pump, &image::arrow, 0);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGuiContext& g = *GImGui;
            const ImGuiStyle& style = g.Style;
                   
            ImGui::GetStyle().ItemSpacing = ImVec2(0, 10);

            CustomStyleColor();
            //ImGui::GetBackgroundDrawList()->AddImage(image::bg, ImVec2(0, 0), ImVec2(1920, 1080), ImVec2(0, 0), ImVec2(1, 1),ImColor(255,255,255,255));

            ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT));
            ImGui::SetNextWindowPos({ 0, 0 });
            ImGui::Begin("IMGUI", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);
            {
                const auto& p = ImGui::GetWindowPos();
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 7, p.y + 10), ImVec2(p.x + 123, p.y + 490), ImGui::GetColorU32(c::other::backgroud),14, ImDrawFlags_RoundCornersLeft);

                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 130 , p.y + 10), ImVec2(p.x + 692, p.y + 60), ImGui::GetColorU32(c::other::backgroud), 3);

                if (Logotip == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, Logo, sizeof(Logo), &info, pump, &Logotip, 0); ImGui::GetForegroundDrawList()->AddImageRounded(Logotip, ImVec2(p.x + 35, p.y + 26), ImVec2(p.x + 95, p.y + 88), ImVec2(0, 0), ImVec2(1, 1), ImColor(47, 189, 255, 255) /*color*/, 0 /*rounding*/);

                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 18, p.y + 104), ImVec2(p.x + 113, p.y + 105),ImColor(91,200,251), 0);
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 18, p.y + 396), ImVec2(p.x + 113, p.y + 397), ImColor(91, 200, 251), 0);
                ImGui::GetWindowDrawList()->AddCircle(ImVec2(p.x + 65, p.y + 443), 25.f, ImColor(47, 189, 255));
                if (User == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, Logo_User, sizeof(Logo_User), &info, pump, &User, 0); ImGui::GetForegroundDrawList()->AddImageRounded(User, ImVec2(p.x + 41, p.y + 419), ImVec2(p.x + 89, p.y + 467), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255) /*color*/, 100 /*rounding*/);
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
                move_window();
            }ImGui::End();
        }     

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_WARP, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
