#pragma once
#include "../Macro.h"
#include "../Window.h"
#include "GfxException.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <vector>

namespace wrl = Microsoft::WRL;

namespace Engine
{
	class DLLEXP GfxBase
	{
	public:
		GfxBase(Window* pWnd);
		~GfxBase();

		void StartRender();
		void EndRender();

	private:
		IDXGIAdapter1* FindSuitableAdapter();
		void BuildSwapChain(HWND hWnd);
		void BuildRenderTargetViewAndDepthView();

	private:
		wrl::ComPtr<IDXGIFactory2> pFactory;
		wrl::ComPtr<IDXGIAdapter1> pAdapter;
		wrl::ComPtr<IDXGISwapChain1> pSwapchain;
		wrl::ComPtr<ID3D11Device> pDevice;
		wrl::ComPtr<ID3D11DeviceContext> pContext;
		wrl::ComPtr<ID3D11RenderTargetView> pRender;
		wrl::ComPtr<ID3D11DepthStencilState> pDepthState;
		wrl::ComPtr<ID3D11DepthStencilView> pDepthView;
		
	};
}
