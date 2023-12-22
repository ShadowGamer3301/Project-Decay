#include "GfxDX/GfxBase.h"

Engine::GfxBase::GfxBase(Window* pWnd)
{
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(pFactory.GetAddressOf()));
	THROW_IF_FAILED(hr);

	pAdapter = FindSuitableAdapter();
	if (pAdapter == nullptr) throw Exception();

	D3D_FEATURE_LEVEL fl[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	hr = D3D11CreateDevice(pAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		fl, _countof(fl), D3D11_SDK_VERSION, pDevice.GetAddressOf(), nullptr, pContext.GetAddressOf());
	THROW_IF_FAILED(hr);

	BuildSwapChain(pWnd->GetWindowHandle());
	BuildRenderTargetViewAndDepthView();
}

Engine::GfxBase::~GfxBase()
{
	SAFERELEASE_COMPTR(pRender);
	SAFERELEASE_COMPTR(pDepthState);
	SAFERELEASE_COMPTR(pDepthView);
	SAFERELEASE_COMPTR(pDevice);
	SAFERELEASE_COMPTR(pAdapter);
	SAFERELEASE_COMPTR(pFactory);
}

IDXGIAdapter1* Engine::GfxBase::FindSuitableAdapter()
{
	UINT i = 0;
	IDXGIAdapter1* pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;
	while (pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 desc;
		pAdapter->GetDesc1(&desc);

		//Check if it's not a software adapter
		if (desc.Flags != DXGI_ADAPTER_FLAG_SOFTWARE)
			//Check if adapter has at least 2GB of VRAM
			if (desc.DedicatedVideoMemory > 2147483648)
			{
				printf("Adapter found: %ls\n", desc.Description);
				return pAdapter;
			}

		SAFE_RELEASE(pAdapter);
	}

	//Show error message if suitable GPU wasn't found
	MessageBox(NULL, L"No suitable adapters found! Please ensure that you have GPU that supports DirectX 11 and has at least 2GB of VRAM",
		L"ERROR: NO GPU", MB_ICONWARNING | MB_OK);
	
	return nullptr;
}

void Engine::GfxBase::BuildSwapChain(HWND hWnd)
{
	//Make sure swapchain is released
	SAFERELEASE_COMPTR(pSwapchain);

	//Clear memory of descriptor
	DXGI_SWAP_CHAIN_DESC1 sdc = { 0 };
	sdc.BufferCount = 1;
	sdc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sdc.Flags = 0;
	sdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sdc.Width = 800;
	sdc.Height = 600;
	sdc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sdc.SampleDesc.Count = 1;
	sdc.SampleDesc.Quality = 0;

	HRESULT hr = pFactory->CreateSwapChainForHwnd(pDevice.Get(), hWnd, &sdc, nullptr, nullptr, pSwapchain.GetAddressOf());
	THROW_IF_FAILED(hr);
}

void Engine::GfxBase::BuildRenderTargetViewAndDepthView()
{
	//Make sure all the reources are released
	SAFERELEASE_COMPTR(pRender);
	SAFERELEASE_COMPTR(pDepthState);
	SAFERELEASE_COMPTR(pDepthView);

	ID3D11Texture2D* pBackBuffer;
	HRESULT hr = pSwapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	THROW_IF_FAILED(hr);

	hr = pDevice->CreateRenderTargetView(pBackBuffer, nullptr, pRender.GetAddressOf());
	THROW_IF_FAILED(hr);

	SAFE_RELEASE(pBackBuffer);

	ID3D11Texture2D* pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = 800;
	descDepth.Height = 600;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	hr = pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
	THROW_IF_FAILED(hr);

	D3D11_DEPTH_STENCIL_DESC dsDesc;
	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	hr = pDevice->CreateDepthStencilState(&dsDesc, pDepthState.GetAddressOf());
	THROW_IF_FAILED(hr);

	pContext->OMSetDepthStencilState(pDepthState.Get(), 0);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;
	hr = pDevice->CreateDepthStencilView(pDepthStencil, &descDSV, pDepthView.GetAddressOf());
	THROW_IF_FAILED(hr);
	SAFE_RELEASE(pDepthStencil);
}

void Engine::GfxBase::StartRender()
{

	float color[] = { 0.0f, 0.2f, 0.6f, 1.0f };
	pContext->ClearRenderTargetView(pRender.Get(), color);
	pContext->ClearDepthStencilView(pDepthView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void Engine::GfxBase::EndRender()
{
	pSwapchain->Present(0, 0);
}