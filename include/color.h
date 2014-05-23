#ifndef __color_h_
#define __color_h_

#include <stdint.h>
#include <math.h>

typedef struct rgb24_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb24;

typedef struct rgb32_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} rgb32;

typedef struct bgr24_t
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} bgr24;

typedef struct bgr32_t
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} bgr32;

typedef struct xyz_t
{
    float x, y, z;
} xyz;

typedef struct hsl_t
{
    float h, s, l;
} hsl;

typedef struct lab_t
{
    float l, a, b;
} lab;

typedef uint32_t Color;

typedef struct ColorData_t
{
    union
    {
        bgr32 bgr;
        Color color;
    };
} ColorData;

#endif // __color_h_
