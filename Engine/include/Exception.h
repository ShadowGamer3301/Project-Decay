/*
    This is class for handling exceptions,
    It provides data about file line & function in which exception occured
*/

#pragma once
#include <exception>
#include <source_location>
#include <string>

namespace Engine {
    #ifdef _WIN32
        class DLLEXP Exception;
    #endif

    class Exception : public std::exception
    {
    public:
        Exception(std::source_location loc = std::source_location::current());
        const char* what() const noexcept override;

    protected:
        std::string file, func;
        unsigned int line;
        mutable std::string wBuffer;
    };
}