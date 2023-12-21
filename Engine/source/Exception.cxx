#include "Exception.h"
#include <sstream>

Engine::Exception::Exception(std::source_location loc)
    : file(loc.file_name()), line(loc.line())
{}

const char* Engine::Exception::what() const noexcept
{
    std::ostringstream oss;
    oss << "Exception caught! \n"
        << "Line: " << line << "\n"
        << "Func: " << func << "\n"
        << "File: " << file << std::endl;

    wBuffer = oss.str();
    return wBuffer.c_str();
}