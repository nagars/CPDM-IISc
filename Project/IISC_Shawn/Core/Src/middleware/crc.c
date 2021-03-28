#include "crc.h"

void append_crc16(const uint16_t crc, uint8_t* data_array,
					const uint8_t size_of_array){

	//append crc to last 2 byts of data array
	data_array[size_of_array - 2] = (uint8_t)(crc >> 8);	//casting uint16_t as uint8_t removed MSB
	data_array[size_of_array - 1] = (uint8_t)crc;

	return;
}

uint16_t calculate_crc16(const int16_t* crc_lookup_table, const uint8_t* data_array,
						uint8_t data_length){

	//Load crc seed value
	uint16_t crc = CRC_SEED;

	//calculate crc for number of bytes specified by user
	while (data_length > 0){
		//Calculate crc
		crc = (crc << 8) ^ crc_lookup_table[((crc >> 8) ^ *data_array++)];
		//Decrement counter
		data_length--;
	}

	return crc;

}

void generate_crc16_msg(const int16_t* crc16_lookup_table, uint8_t* data_array,
						const uint8_t array_length){

	//16bits should already have been appended to data buffer

	//encode crc
	int16_t crc = calculate_crc16(crc16_lookup_table, data_array, array_length);

	//append crc to data
	append_crc16(crc, data_array, array_length);

	return;
}

bool check_crc16(){

	//Performs crc checks

	//returns success / failure
	return SUCCESS;
}
