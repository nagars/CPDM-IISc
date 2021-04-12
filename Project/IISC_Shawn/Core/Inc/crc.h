#ifndef CRC_H
#define CRC_H

#include "definitions.h"

/**
 * @file crc.h
 * @brief This driver performs crc coding and decoding. It implements
 * a crc16 - citt polynomial (x16 + x12 + x5 + 1) = 0x1021.
 *
 * @par feature list:
 * 1, Encode a msg to transmit with a calculated crc
 * 2, Decode incoming data through crc algorithm and lookup table
 * 3, Use polynomial value 0x1021 (x16 + x12 + x5 + 1)
 * 4, Return a status indicating if crc check was passed or not
 * 5, Use a pre-determined lookup table to improve crc calculation speed
 * 6, Array given should have last 2 bytes available for crc append
 *
 * @par References
 * 1, https://cs.fit.edu/code/svn/cse2410f13team7/wireshark/wsutil/crc16.c
 * 2, http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch4
 * 3, https://stackoverflow.com/questions/22432066/how-to-use-table-based-crc-16-code
 * 4, https://stackoverflow.com/questions/43279590/crc32c-appending-0s-crc-to-message
 * 5, https://www.geeksforgeeks.org/modulo-2-binary-division/#:~:text=The%20process%20of%20modulo%2D2,the%20dividend%20(or%20key).
 */

#ifndef CRC_SEED
	#define CRC_SEED 0xffff
#endif

//Lookup table for crc16
extern const int16_t crc16_ccitt_table[256];

/**
 * @brief Description: Calculates crc and appends calculated crc to msg
 *
 * @param const int16_t* : Lookup table to use for crc generation
 * @param uint8_t* : Data array to generate crc for and append to
 * @param const uint8_t : Size of data array (Ignore last 2 bytes reserved for crc)
 *
 * @return void
 */
void generate_crc16_msg(const int16_t*, uint8_t*, const uint8_t);

/**
 * @brief Description: appends calculated crc for outgoing message
 *
 * @param const int16_t : crc
 * @param uint8_t* : Data array to append crc to
 * @param const uint8_t : Size of data array
 *
 * @return void
 */
void append_crc16(const uint16_t, uint8_t*, const uint8_t);

/**
 * @brief Description: calculates crc for given data array
 *
 * @param const int16_t : Lookup table to use for calculation
 * @param const uint8_t* : Data array to generate crc for
 * @param const uint8_t : Size of data array
 *
 * @return uint16_t : crc calculated
 */
uint16_t calculate_crc16(const int16_t*, const uint8_t*, uint8_t);

/**
 * @brief Description: Checks if incoming message is valid using crc16
 *
 * @param const int16_t : Lookup table to use for calculation
 * @param const uint8_t* : Data array to generate crc for
 * @param const uint8_t : Size of data array(Including 2 bytes reserved for crc)
 *
 * @return bool : 1 if success, 0 if failed check
 */
bool check_crc16(const int16_t*, const uint8_t*, uint8_t);


#endif
