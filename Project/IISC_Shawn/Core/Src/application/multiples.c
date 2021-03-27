#include "multiples.h"
#include <string.h>

void check_multiples(uint8_t val, char* msg){

	//init variable to hold code indicating if val is a multiple of 4,7,both or neither
	uint8_t multiple_code = 0;

	//check for 4 (Assigned to bit0)
	multiple_code = check_multiple_of_4(val);

	//check for 7 (Left shifted for bit1)
	multiple_code |= check_multiple_of_7(val) << 1;

	char c_val = (char)val;
	//prepare message
	switch(multiple_code){
	case 0b00:
		strcpy(msg, &c_val);
		break;
	case 0b01:
		strcpy(msg, "CPDM");
		break;
	case 0b10:
		strcpy(msg,"IISc");
		break;
	case 0b11:
		strcpy(msg,"CPDM IISc");
		break;
	default:
		break;
	}

	return;
}

bool check_multiple_of_4(uint8_t val){

	/*https://www.geeksforgeeks.org/efficiently-check-whether-n-multiple-4-not/*/

	//Last 2 bits of a number divisible by 4 are 0
	if((val & 3) == 0){
		return true;
	}

	return false;
}

bool check_multiple_of_7(int8_t val){

	/*https://www.geeksforgeeks.org/divisibility-by-7/#:~:
	text=Divisibility%20by%207%20can%20be,this%20until%20a%20small%20number.*/

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
