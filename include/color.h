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
    float x;
    float y;
    float z;
} xyz;

typedef struct hsl_t
{
    float h;
    float s;
    float l;
} hsl;

typedef struct lab_t
{
    float l;
    float a;
    float b;
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


/** @brief A function for converting RGB pixel format to XYZ pixel format.
 *
 * @param px rgb32* A pointer to an RGB structure to be converted.
 * @return xyz An XYZ structure containing the converted contents.
 *
 */
extern xyz rgb_to_xyz(rgb32 *px);


/** @brief A function for converting XYZ pixel format to RGB pixel format.
 *
 * @param px xyz* A pointer to an XYZ structure to be converted.
 * @return rgb32 A RGB structure containing the converted contents.
 *
 */
extern rgb32 xyz_to_rgb(xyz *px);


/** @brief A function for converting RGB pixel format to HSL pixel format.
 *
 * @param px rgb32* A pointer to an RGB structure to be converted.
 * @return hsl An HSL structure containing the converted contents.
 *
 */
extern hsl rgb_to_hsl(rgb32 *px);


/** @brief A function for converting HSL pixel format to RGB pixel format.
 *
 * @param px hsl* A pointer to an HSL structure to be converted.
 * @return rgb32 An RGB structure containing the converted contents.
 *
 */
extern rgb32 hsl_to_rgb(hsl *px);


/** @brief A function for converting XYZ pixel format to LAB pixel format.
 *
 * @param px xyz* A pointer to an XYZ structure to be converted.
 * @return lab An LAB structure containing the converted contents.
 *
 */
extern lab xyz_to_lab(xyz *px);


/** @brief A function for converting LAB pixel format to RGB pixel format.
 *
 * @param px lab* A pointer to an LAB structure to be converted.
 * @return xyz An XYZ structure containing the converted contents.
 *
 */
extern xyz lab_to_xyz(lab *px);

#endif // __color_h_
