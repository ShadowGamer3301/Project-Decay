#pragma once

#if defined (WIN32) || defined (_WIN32)
    #ifdef _WINDLL
        #define DLLEXP __delcpsec(dllexport)
    #else
        #define DLLEXP __delcpsec(dllimport)
    #endif

    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX //since it can override the stdlib function

#endif

#define DELETE_ON_VAL(p) if(p) delete p