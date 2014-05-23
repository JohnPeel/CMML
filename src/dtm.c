#include "dtm.h"

bool resizeDTM(MDTM *dtm, uint32_t size)
{
    MDTMPoint *points;
    if (dtm->count > 0)
    {
        points = (MDTMPoint *)realloc(dtm->points, size * sizeof(MDTMPoint));
        //TODO: memset points + oldsize, size - oldsize, with \0
    }
    else
        points = (MDTMPoint *)calloc(size, sizeof(MDTMPoint));

    if (points == NULL)
        return false;

    dtm->points = points;
    dtm->count = size;
    return true;
}

void normalizeDTM(MDTM *dtm)
{
    if ((dtm->count < 1) || ((dtm->points[0].x == 0) && (dtm->points[0].y == 0)))
        return;

    uint32_t index;
    for (index = 1; index < dtm->count; index++)
    {
        dtm->points[index].x -= dtm->points[0].x;
        dtm->points[index].y -= dtm->points[0].y;
    }

    dtm->points[0].x = 0;
    dtm->points[0].y = 0;
}

bool isDTMValid(MDTM *dtm)
{
    if (dtm->count < 1)
        return false;
    normalizeDTM(dtm);
    return true;
}

char *stringFromDTM(MDTM *dtm)
{
    if (dtm->count < 1)
        return "";

    uint32_t size = (sizeof(MDTMPoint) + sizeof(uint32_t)) * dtm->count;
    void *data = calloc(1, size);
    uint32_t *ptr = data;
    *(ptr++) = size;

    uint32_t index;

    for (index = 0; index < dtm->count; index++)
        *(ptr++) = dtm->points[index].x;
    for (index = 0; index < dtm->count; index++)
        *(ptr++) = dtm->points[index].y;
    for (index = 0; index < dtm->count; index++)
        *(ptr++) = dtm->points[index].color;
    for (index = 0; index < dtm->count; index++)
        *(ptr++) = dtm->points[index].tol;
    for (index = 0; index < dtm->count; index++)
        *(ptr++) = dtm->points[index].size;
    for (index = 0; index < dtm->count; index++)
        *(ptr++) = dtm->points[index].x;

    bool *bptr = (bool *)ptr;
    for (index = 0; index < dtm->count; index++)
        *(bptr++) = dtm->points[index].bad;

    uint32_t len = compressBound(size);
    char *buffer = malloc(len);
    if (compress((Bytef *)buffer, (uLongf *)&len, data, size) == Z_OK)
    {
        free(data);

        char *compressed = malloc(len + sizeof(uint32_t));
        *((uint32_t *)(compressed)) = len;
        strcpy(compressed + sizeof(uint32_t), buffer);
        free(buffer);

        //TODO: return "m" + base64encode(ret);
    }

    free(buffer);
    free(data);
    return "";
}

MDTM stringToDTM(char *string)
{
    MDTM dtm;
    return dtm;
}

uint32_t addDTMPoint(MDTM *dtm, MDTMPoint point)
{
    resizeDTM(dtm, dtm->count + 1);

    uint32_t index = dtm->count - 1;
    dtm->points[index] = point;
    return index;
}

void removeDTMPoint(MDTM *dtm, uint32_t index)
{
    uint32_t cur;
    for (cur = index + 1; cur < dtm->count; cur++)
        swapDTMPoints(dtm, cur - 1, cur);
    resizeDTM(dtm, dtm->count - 1);
}

void swapDTMPoints(MDTM *dtm, uint32_t first, uint32_t second)
{
    MDTMPoint tempPoint = dtm->points[first];
    dtm->points[first] = dtm->points[second];
    dtm->points[second] = tempPoint;
}
