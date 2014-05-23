#ifndef __eios_h_
#define __eios_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "dl.h"
#include "color.h"

#ifdef __i386__
#define stdcall __attribute__((stdcall))
#else
#define stdcall
#endif // __i386__

typedef void *(*requestTargetT)(char *initargs) stdcall;
typedef void (*releaseTargetT)(void *target) stdcall;

typedef void (*getTargetDimensionsT)(void *target, uint32_t *width, uint32_t *height) stdcall;
typedef void (*getTargetPositionT)(void *target, uint32_t *left, uint32_t *top) stdcall;

typedef ColorData *(*getImageBufferT)(void *target) stdcall;
typedef void (*updateImageBufferT)(void *target) stdcall;
typedef void (*updateImageBufferBoxT)(void *target, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) stdcall;

typedef void (*getMousePositionT)(void *target, uint32_t *x, uint32_t *y) stdcall;
typedef void (*moveMouseT)(void *target, uint32_t x, uint32_t y) stdcall;
typedef void (*scrollMouseT)(void *target, uint32_t x, uint32_t y, uint32_t lines) stdcall;
typedef void (*holdMouseT)(void *target, uint32_t x, uint32_t y, uint32_t button) stdcall;
typedef void (*releaseMouseT)(void *target, uint32_t x, uint32_t y, uint32_t button) stdcall;
typedef bool (*isMouseButtonHeldT)(void *target, uint32_t button) stdcall;

typedef void (*sendStringT)(void *target, char *str, uint32_t keywait, uint32_t keymodwait) stdcall;
typedef void (*holdKeyT)(void *target, uint32_t key) stdcall;
typedef void (*releaseKeyT)(void *target, uint32_t key) stdcall;
typedef bool (*isKeyHeldT)(void *target, uint32_t key) stdcall;
typedef void (*getKeyCodeT)(void *target, char c) stdcall;

typedef struct EIOSClient_t
{
    void *libHandle;

    requestTargetT requestTarget;
    releaseTargetT releaseTarget;

    getTargetDimensionsT getTargetDimensions;
    getTargetPositionT getTargetPosition;

    getImageBufferT getImageBuffer;
    updateImageBufferT updateImageBuffer;
    updateImageBufferBoxT updateImageBufferBox;

    getMousePositionT getMousePosition;
    moveMouseT moveMouse;
    scrollMouseT scrollMouse;
    holdMouseT holdMouse;
    releaseMouseT releaseMouse;
    isMouseButtonHeldT isMouseButtonHeld;

    sendStringT sendString;
    holdKeyT holdKey;
    releaseKeyT releaseKey;
    isKeyHeldT isKeyHeld;
    getKeyCodeT getKeyCode;
} EIOSClient;

extern bool loadEIOSClient(EIOSClient *client, char *path);
extern void unloadEIOSClient(EIOSClient *client);

#endif // __eios_h_
