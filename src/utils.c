#include "utils.h"


bool base64encode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len)
{
    int i, j;
    char *ptr;
    uint32_t c[4];
    static char indexes[] = {0, 2, 1};
    static const char *Base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    *out_len = 4 * ((in_len + 2) / 3);
    *out = malloc(*out_len + 1);
    ptr = *out;

    if (*out)
    {
        for (i = 0, j = 0; i < in_len;)
        {
            c[0] = i < in_len ? in[i++] : 0;
            c[1] = i < in_len ? in[i++] : 0;
            c[2] = i < in_len ? in[i++] : 0;

            c[3] = (c[0] << 0x10) + (c[1] << 0x08) + c[2];

            ptr[j++] = Base64Chars[(c[3] >> 3 * 6) & 0x3F];
            ptr[j++] = Base64Chars[(c[3] >> 2 * 6) & 0x3F];
            ptr[j++] = Base64Chars[(c[3] >> 1 * 6) & 0x3F];
            ptr[j++] = Base64Chars[(c[3] >> 0 * 6) & 0x3F];
        }

        for (i = 0; i < indexes[in_len % 3]; ++i)
            ptr[*out_len - 1 - i] = '=';

        ptr[*out_len] = '\0';
        return true;
    }

    *out_len = 0;
    return false;
}

bool base64decode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len)
{
    int i, j;
    char *ptr;
    uint32_t c[5];
    static char table[256];
    static const char *Base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    if (in_len % 4 != 0)
        return false;

    *out_len = in_len / 4 * 3;
    if (in[in_len - 1] == '=') --(*out_len);
    if (in[in_len - 2] == '=') --(*out_len);

    *out = malloc(*out_len);
    ptr = *out;

    if (*out)
    {
        for (i = 0; i < 64; ++i)
            table[(uint8_t)Base64Chars[i]] = i;

        for (i = 0, j = 0; i < in_len;)
        {
            c[0] = in[i] == '=' ? 0 & i++ : table[(uint8_t)in[i++]];
            c[1] = in[i] == '=' ? 0 & i++ : table[(uint8_t)in[i++]];
            c[2] = in[i] == '=' ? 0 & i++ : table[(uint8_t)in[i++]];
            c[3] = in[i] == '=' ? 0 & i++ : table[(uint8_t)in[i++]];
            c[4] = (c[0] << 3 * 6) + (c[1] << 2 * 6) + (c[2] << 1 * 6) + (c[3] << 0 * 6);

            if (j < *out_len) ptr[j++] = (c[4] >> 2 * 8) & 0xFF;
            if (j < *out_len) ptr[j++] = (c[4] >> 1 * 8) & 0xFF;
            if (j < *out_len) ptr[j++] = (c[4] >> 0 * 8) & 0xFF;
        }

        ptr[*out_len] = '\0';
        return true;
    }

    *out_len = 0;
    return false;
}
