#ifndef __utils_h_
#define __utils_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool base64encode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len);
bool base64decode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len);

#endif // __utils_h_
