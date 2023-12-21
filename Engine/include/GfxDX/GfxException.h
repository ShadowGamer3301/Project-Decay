#pragma once
#include "../Macro.h"
#include "../Exception.h"
#include <Windows.h>

namespace Engine
{
	class DLLEXP GfxException : public Exception
	{
	public:
		GfxException(HRESULT hr, std::source_location loc = std::source_location::current());
		const char* what() const noexcept override;

	private:
		HRESULT hr;
	};
}