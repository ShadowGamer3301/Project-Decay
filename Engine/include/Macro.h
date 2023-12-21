#pragma once

#if defined (WIN32) || defined (_WIN32)
    #ifdef _WINDLL
        #define DLLEXP __declspec(dllexport)
    #else
        #define DLLEXP __declspec(dllimport)
    #endif

    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX //since it can override the stdlib function
    
    #define THROW_IF_FAILED(hr) if(FAILED(hr)) throw GfxException(hr)
    #define SAFE_RELEASE(p) if(p) p->Release()
#endif

#define DELETE_ON_VAL(p) if(p) delete p