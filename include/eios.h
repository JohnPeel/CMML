#ifndef __eios_h_
#define __eios_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "color.h"

#ifndef __i386__
#ifdef _M_IX86
#define __i386__
#endif // _M_IX86
#endif // __i386__

#ifdef __i386__
#define stdcall __attribute__((stdcall))
#else
#define stdcall
#endif // __i386__

typedef struct EIOSClient_t
{
    void *libHandle;

    void *(*requestTarget)(char *initargs) stdcall;
    void (*releaseTarget)(void *target) stdcall;

    void (*getTargetDimensions)(void *target, uint32_t *width, uint32_t *height) stdcall;
    void (*getTargetPosition)(void *target, uint32_t *left, uint32_t *top) stdcall;

    ColorData *(*getImageBuffer)(void *target) stdcall;
    void (*updateImageBuffer)(void *target) stdcall;
    void (*updateImageBufferBox)(void *target, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) stdcall;

    void (*getMousePosition)(void *target, uint32_t *x, uint32_t *y) stdcall;
    void (*moveMouse)(void *target, uint32_t x, uint32_t y) stdcall;
    void (*scrollMouse)(void *target, uint32_t x, uint32_t y, uint32_t lines) stdcall;
    void (*holdMouse)(void *target, uint32_t x, uint32_t y, uint32_t button) stdcall;
    void (*releaseMouse)(void *target, uint32_t x, uint32_t y, uint32_t button) stdcall;
    bool (*isMouseButtonHeld)(void *target, uint32_t button) stdcall;

    void (*sendString)(void *target, char *str, uint32_t keywait, uint32_t keymodwait) stdcall;
    void (*holdKey)(void *target, uint32_t key) stdcall;
    void (*releaseKey)(void *target, uint32_t key) stdcall;
    bool (*isKeyHeld)(void *target, uint32_t key) stdcall;
    void (*getKeyCode)(void *target, char c) stdcall;
} EIOSClient;

/** @brief A function for abstracting away platform specific loading of modules.
 *
 * @param libname const char* Name of the module to be loaded.
 * @return void* A pointer to the loaded module's handle. NULL is returned upon failure.
 *
 */
extern inline void *loadModule(const char *libname);


/** @brief A function for abstracting away platform specific freeing of modules.
 *
 * @param module void* A pointer to the module's handle to be freed.
 * @return int On Linux systems, the return value of this function is 0 upon success. Non-zero otherwise.
 *             On Windows systems, the return value of this function is non-zero upon success. 0 otherwise.
 *
 */
extern inline int freeModule(void *module);


/** @brief A function for abstracting away platform specific retrieval of function addresses from a module.
 *
 * @param module void* A pointer to the loaded module's handle that contains the specified function.
 * @param proc_name const char* Name of the function whose address is to be retrieved.
 * @return void* A pointer containing the address of the specified function upon success. NULL is returned upon failure.
 *
 */
extern inline void *getFuncAddress(void *module, const char *proc_name);


extern bool loadEIOSClient(EIOSClient *client, char *path);
extern void unloadEIOSClient(EIOSClient *client);

#endif // __eios_h_
