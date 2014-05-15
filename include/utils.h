#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool base64encode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len);
bool base64decode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len);

#endif // UTILS_H_INCLUDED
