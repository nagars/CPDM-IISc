#include "multiples.h"
#include <string.h>

uint8_t check_multiples(const uint8_t val, unsigned char* msg){

	//init variable to hold code indicating if val is a multiple of 4,7,both or neither
	uint8_t multiple_code = 0;

	//check for 4 (Assigned to bit0)
	multiple_code = check_multiple_of_4(val);

	//check for 7 (Left shifted for bit1)
	multiple_code |= check_multiple_of_7(val) << 1;

	//prepare message
	switch(multiple_code){
	case 0b00:
		memcpy(msg, &val, 1);
		break;
	case 0b01:
		memcpy(msg, "CPDM", 4);
		break;
	case 0b10:
		memcpy(msg,"IISc", 4);
		break;
	case 0b11:
		memcpy(msg,"CPDM IISc", 9);
		break;
	default:
		break;
	}

	//return length of response message
	return strlen(msg);
}

bool check_multiple_of_4(uint8_t val){

	//Last 2 bits of a number divisible by 4 are 0
	if((val & 3) == 0){
		return true;
	}

	return false;
}

bool check_multiple_of_7(int8_t val){

	if(val < 0){
		val = -val;
	}

	//7 is a multiple of itself
	if((val == 7)||(val == 0)){
		return true;
	}

	//closest multiple of 7 is more than 10
	if(val < 10){
		return false;
	}

	return check_multiple_of_7(val/10 - 2*(val - (val/10)*10));

}
