#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/** @brief Encodes a buffer to the Bas64 string representation.
 *
 * @param in const uint8_t* Pointer to the buffer to be encoded.
 * @param in_len uint32_t Length of the buffer in bytes.
 * @param out char** Pointer to a string that will hold the encoded buffer. Pointer must point to nil.
                     Must be freed using free() when finished with it.
 * @param out_len uint32_t* Pointer to an unsigned integer that will hold the length of the encoded buffer.
 * @return bool Returns true if the encoding was successful; false otherwise.
 *
 */
extern bool base64encode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len);


/** @brief Decodes a Base64 encoded buffer back into its original representation.
 *
 * @param in const uint8_t* Pointer to the Base64 encoded buffer.
 * @param in_len uint32_t Length of the buffer containing the Base64 string.
 * @param out char** Pointer to a string that will hold the decoded buffer. Pointer must point to nil.
                     Must be freed using free() when finished with it.
 * @param out_len uint32_t* Pointer to an unsigned integer that will hold the length of the decoded buffer.
 * @return extern bool Returns true if the decoding was successful; false otherwise.
 *
 */
extern bool base64decode(const uint8_t *in, uint32_t in_len, char **out, uint32_t *out_len);

#endif // UTILS_H_INCLUDED
