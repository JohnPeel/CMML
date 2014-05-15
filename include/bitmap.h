#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "color.h"
#include "utils.h"
#include "zlib.h"

typedef struct bitmap_t {
  uint32_t width;
  uint32_t height;
  rgb32 *pixels;
} bitmap;



extern bool createbitmap(bitmap *bmp, uint32_t width, uint32_t height);
extern bool copybitmap(bitmap *in, bitmap *out);
extern bool bitmap_from_file(bitmap *bmp, const char *filepath);
extern bool bitmap_from_24bit_string(bitmap *bmp, const char *str);
extern bool bitmap_from_32bit_string(bitmap *bmp, const char *str);
extern bool savebmp(bitmap *bmp, const char *filepath, uint16_t bpp);
extern bool bitmap_to_24bit_string(bitmap *bmp, char **str, uint32_t *len);
extern bool bitmap_to_32bit_string(bitmap *bmp, char **str, uint32_t *len);
extern void freebmp(bitmap *bmp);

#endif
