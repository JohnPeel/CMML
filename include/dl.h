#ifndef __dl_h_
#define __dl_h_

#if defined _WIN32 || defined _WIN64
#define WINDOWS
#include <windows.h>

#define loadModule(x) LoadLibrary(x)
#define freeModule(x) FreeLibrary(x)
#define getModuleFunc(x, y) GetProcAddress(x, y)
#else
#define UNIX
#include <dlfcn.h>

#define loadModule(x) dlopen(x, RTLD_LAZY)
#define freeModule(x) dlclose(x)
#define getModuleFunc(x, y) dlsym(x, y)
#endif

#ifndef __i386__
#ifdef _M_IX86
#define __i386__
#endif // _M_IX86
#endif // __i386__

#endif // __dl_h_
