#ifndef __target_h_
#define __target_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include "color.h"
#include "eios.h"
#include "input.h"

typedef struct RawTarget_t
{
    uint32_t width;
    uint32_t height;
    ColorData *data;
} RawTarget;

typedef struct EIOSTarget_t
{
    EIOSClient *client;
    void *target;
    ColorData *buffer;
} EIOSTarget;

typedef struct ClientArea_t
{
    uint32_t x1;
    uint32_t y1;
    uint32_t x2;
    uint32_t y2;
} ClientArea;

typedef struct TargetData_t
{
    ColorData *data;
    uint32_t rowWidth;
    uint32_t incData;
} TargetData;

typedef enum {RawKind, EIOSKind} TargetKind;
typedef struct Target_t
{
    TargetKind kind;
    union
    {
        RawTarget rawData;;
        EIOSTarget eiosData;
    };
    bool clientAreaSet;
    ClientArea clientArea;
    TargetData targetData;
} Target;

extern void getTargetDimensions(Target *target, uint32_t *width, uint32_t *height);
extern void getTargetPosition(Target *target, uint32_t *left, uint32_t *top);
extern Color getTargetPixel(Target *target, uint32_t x, uint32_t y);
extern TargetData getTargetData(Target *target, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
extern void freeTargetData(Target *target);

extern void getTargetMousePos(Target *target, uint32_t *x, uint32_t *y);
extern void setTargetMousePos(Target *target, uint32_t x, uint32_t y);
extern MouseAction getTargetMouseAction(Target *target, MouseButton button);
extern void setTargetMouseAction(Target *target, MouseAction action, MouseButton button);
extern KeyAction getTargetKeyAction(Target *target, uint32_t key);
extern void setTargetKeyAction(Target *target, KeyAction action, uint32_t key);

extern bool setTargetClientArea(Target *target, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
extern void resetTargetClientArea(Target *target);

#endif // __target_h_
