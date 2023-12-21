#include "GfxDX/GfxException.h"
#include <sstream>

Engine::GfxException::GfxException(HRESULT hr, std::source_location loc)
	: hr(hr), Exception(loc)
{}

const char* Engine::GfxException::what() const noexcept
{
	std::ostringstream oss;
	oss << "Graphics (DirectX 11) exception caught!\n"
		<< "Line: " << line << "\n"
		<< "Func: " << func << "\n"
		<< "File: " << file << std::endl;

	wBuffer = oss.str();

	return wBuffer.c_str();
}