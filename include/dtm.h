#ifndef __dtm_h_
#define __dtm_h_

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "zlib.h"
#include "color.h"

typedef struct
{
    int32_t x;
    int32_t y;
    Color color;
    uint32_t tol;
    uint32_t size;
    bool bad;
} MDTMPoint;

typedef struct
{
    char *name;
    int32_t index;
    MDTMPoint* points;
    uint32_t count;
} MDTM;

typedef struct
{
    int32_t x;
    int32_t y;
    Color color;
    uint32_t tol;
    uint32_t size;
    uint32_t shape;
} SDTMPoint;

typedef struct
{
    SDTMPoint main;
    SDTMPoint* points;
} SDTM;

extern void normalizeDTM(MDTM *dtm);
extern bool isDTMValid(MDTM *dtm);
extern char *stringFromDTM(MDTM *dtm);
extern MDTM stringToDTM(char *string);
extern uint32_t addDTMPoint(MDTM *dtm, MDTMPoint point);
extern void removeDTMPoint(MDTM *dtm, uint32_t index);
extern void swapDTMPoints(MDTM *dtm, uint32_t first, uint32_t second);

#endif //__dtm_h_
