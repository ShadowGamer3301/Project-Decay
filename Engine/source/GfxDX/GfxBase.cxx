#include "GfxDX/GfxBase.h"

Engine::GfxBase::GfxBase(Window* pWnd)
{
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(pFactory.GetAddressOf()));
	THROW_IF_FAILED(hr);

	pAdapter = FindSuitableAdapter();
	if (pAdapter == nullptr) throw Exception();

}

Engine::GfxBase::~GfxBase()
{
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

		if (desc.Flags != DXGI_ADAPTER_FLAG_SOFTWARE)
			if (desc.DedicatedVideoMemory > 2147483648)
			{
				printf("Adapter found: %ls\n", desc.Description);
				return pAdapter;
			}
	}

	MessageBox(NULL, L"No suitable adapters found! Please ensure that you have GPU that supports DirectX 11 and has at least 2GB of VRAM",
		L"ERROR: NO GPU", MB_ICONWARNING | MB_OK);
	
	return nullptr;
}