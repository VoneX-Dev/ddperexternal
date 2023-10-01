#pragma once
#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>
#include <aimbot.h>
#include <player.h>
#include <server.h>
#include <esp.h>

#include <imgui/imgui.h>

namespace ui
{

	inline const int GUI_WIDTH = 500;
	inline const int GUI_HEIGHT = 400;

	inline HWND window = nullptr;
    inline WNDCLASSEXW wc{};

	inline bool isRunning = true;
	inline bool isMenuOpen = false;

	inline POINTS position = { };

	inline ID3D11Device* device = nullptr;
    inline ID3D11DeviceContext* device_context = nullptr;
    inline IDXGISwapChain* swap_chain = nullptr;
    inline ID3D11RenderTargetView* render_target_view = nullptr;
    inline D3D_FEATURE_LEVEL level;

	void CreateHUIWindow() noexcept;
	void DestroyHUIWindow() noexcept;

	bool CreateUIDevice() noexcept;
	void ResetUIDevice() noexcept;
	void DestroyUIDevice() noexcept;

	void CreateUIImGui() noexcept;
	void DestroyUIImGui() noexcept;

	void BeginRenderUI() noexcept;
	void EndRenderUI() noexcept;
	void RenderUI(Aimbot *aimbot, ESP *esp, Server *server) noexcept;

	void SetMenuOpen() noexcept;
	void SetMenuClose() noexcept;
}
