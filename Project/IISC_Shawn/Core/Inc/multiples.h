#ifndef MULTIPLES_H
#define MULTIPLES_H

#include "definitions.h"

/**
 * @file multiples.h
 * @brief This driver implements functions checking if the give value is a multiple of
 * 4 and/or 7.
 *
 * @par Feature List:
 * 1, Checks if a value is a multiple of 4
 * 2, Checks if a value is a multiple of 7
 * 3, Generates a response message based on the result of checking
 *
*/

/**
 * @brief Description: Calls functions to check if data is a multiple
 * of 4 and/or 7. Generates response message
 *
 * @parm const uint8_t : data value to check
 * @param unsigned char* : Pointer to character buffer to store response message
 *
 * @return uint8_t : size of msg
 */
uint8_t check_multiples(const uint8_t, unsigned char*);

/**
 * @brief Description: Checks if the given value is a multiple of 4
 *
 * @parm uint8_t : Data to check
 *
 * @return bool : 1 if number is a multiple, else 0
 */
bool check_multiple_of_4(uint8_t);

/**
 * @brief Description: Checks if the given value is a multiple of 7
 *
 * @parm int8_t : Data to check
 *
 * @return bool : 1 if number is a multiple, else 0
 */
bool check_multiple_of_7(int8_t);

#endif
