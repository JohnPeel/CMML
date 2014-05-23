#ifndef __bitmap_h_
#define __bitmap_h_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "color.h"
#include "utils.h"
#include "zlib.h"

typedef struct bitmap_t
{
    uint32_t width;
    uint32_t height;
    rgb32 *pixels;
} bitmap;



/** @brief Creates a bitmap with all pixels set to black.
 *
 * @param bmp bitmap* Pointer to a bitmap structure that will be filled.
 * @param width uint32_t The width of the bitmap to be created.
 * @param height uint32_t The height of the bitmap to be created.
 * @return bool Returns true if successful; false otherwise.
 *
 */
extern bool createbitmap(bitmap *bmp, uint32_t width, uint32_t height);

/** @brief Creates a copy of a bitmap.
 *
 * @param in bitmap* Pointer to a bitmap structure to be copied.
 * @param out bitmap* Pointer to a bitmap structure to copy to.
 * @return bool Returns true if the second bitmap was created successfully; false otherwise.
 *
 */
extern bool copybitmap(bitmap *in, bitmap *out);


/** @brief Reads a bitmap from a file.
 *
 * @param bmp bitmap* Pointer to a bitmap structure that will hold the information read.
 * @param filepath const char* Location of the bitmap file to be read.
 * @return bool Returns true if the file can be read and the bitmap can be stored; false otherwise.
 *
 */
extern bool bitmap_from_file(bitmap *bmp, const char *filepath);


/** @brief Converts a string representation of a 24-bit bitmap to a 32-bit bitmap structure.
 *
 * @param bmp bitmap* Pointer to the bitmap structure that will hold the deserialized data.
 * @param str const char* String to convert into a bitmap.
 * @return bool Returns true if the conversion is successful and the string is valid; false otherwise.
 *
 */
extern bool bitmap_from_24bit_string(bitmap *bmp, const char *str);


/** @brief Converts a string representation of a 32-bit bitmap to a 32-bit bitmap structure.
 *
 * @param bmp bitmap* Pointer to the bitmap structure that will hold the deserialized data.
 * @param str const char* String to convert into a bitmap.
 * @return bool Returns true if the conversion is successful and the string is valid; false otherwise.
 *
 */
extern bool bitmap_from_32bit_string(bitmap *bmp, const char *str);


/** @brief Saves/Writes a bitmap to the disk.
 *
 * @param bmp bitmap* Pointer to the bitmap structure representing the bitmap to be written/saved.
 * @param filepath const char* Location/Path with the file-name of where the bitmap should be saved.
 * @param bpp uint16_t Bits per pixel (represents the format the bitmap will be saved in). Can be 24bit or 32bit ONLY.
 * @return bool Returns true if the bitmap was saved successfully; false otherwise.
 *
 */
extern bool savebmp(bitmap *bmp, const char *filepath, uint16_t bpp);


/** @brief Converts a bitmap structure into a 24-bit bitmap string representation. Alpha channel is not preserved.
 *
 * @param bmp bitmap* Pointer to the bitmap structure to be serialized.
 * @param str char** Pointer to a string that will hold the serialized bitmap. This pointer must point to nil.
 *                   Developers must call free() on this pointer when finished with it.
 * @param len uint32_t* Pointer to an unsigned integer that will hold the length of the serialized string.
 * @return bool Returns true if the conversion was successful; false otherwise.
 *
 */
extern bool bitmap_to_24bit_string(bitmap *bmp, char **str, uint32_t *len);


/** @brief Converts a bitmap structure into a 32-bit bitmap string representation. Alpha channel is preserved.
 *
 * @param bmp bitmap* Pointer to the bitmap structure to be serialized.
 * @param str char** Pointer to a string that will hold the serialized bitmap. The pointer must point to nil.
 *                   Developers must call free() on this pointer when finished with it.
 * @param len uint32_t* Pointer to an unsigned integer that will hold the length of the serialized string.
 * @return bool Returns true if teh conversion was successful; false otherwise.
 *
 */
extern bool bitmap_to_32bit_string(bitmap *bmp, char **str, uint32_t *len);


/** @brief Frees/Deallocates a bitmap structure.
 *
 * @param bmp bitmap* Pointer to the bitmap structure to be freed.
 * @return void
 *
 */
extern void freebmp(bitmap *bmp);

#endif // __bitmap_h_
