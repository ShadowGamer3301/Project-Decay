#include "GfxDX/GfxBase.h"

Engine::GfxBase::GfxBase(Window* pWnd)
{
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(pFactory.GetAddressOf()));
	THROW_IF_FAILED(hr);

	pAdapter = FindSuitableAdapter();
}

Engine::GfxBase::~GfxBase()
{
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);
}

IDXGIAdapter* Engine::GfxBase::FindSuitableAdapter()
{
	UINT i = 0;
	IDXGIAdapter* pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;
	while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		++i;
	}
	
	//For now return first found adapter (replace it later)
	return vAdapters[0];
}