#ifndef __eios_h_
#define __eios_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

#include "color.h"

#ifdef _WIN32
#define stdcall __attribute__((stdcall))
#else
#define stdcall 
#endif

typedef struct EIOSClient_t {
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

extern bool loadEIOSClient(EIOSClient *client, char *path);
extern void unloadEIOSClient(EIOSClient *client);

#endif