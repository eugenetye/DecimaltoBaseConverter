#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// TODO: what are function prototypes?
void other_base(unsigned, unsigned);
void power2_base(unsigned, unsigned);
void base_256(unsigned, unsigned);

// this will not change, so we can declare it constant
const char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";

// this _will_ change, however
char buffer[32];
int pointer = 31;

// every C program must implement the `main()` function
int main(int argc, char *argv[]){

	// TODO: error check
	// if (argc != 3) then...
	if (argc == 1 || argc != 3){					// no. of arguments must be 3 including ./conv
		printf("Usage: ./conv <decimal> <base>\n");
		return -1;
	}

	// properly NULL terminate the buffer
	buffer[pointer] = 0;
	pointer -= 1;

	// use `atoi()` function to translate characters to numbers
	unsigned decimal = atoi(argv[1]);
	unsigned base    = atoi(argv[2]);

	// show an error if user supplies a non-number argument to the <decimal> argument 
	if (decimal == 0){
        printf("INVALID NUMBER\n");
	    return -1;
	}

	// TODO: decide which function to call based on
	// the user's desired base
	if (base >= 2 && base <= 64){				
	    if  ((base &(base - 1)) == 0){			// if the output of bitwise AND between base and (base - 1) is 0, this means
			power2_base(decimal, base);			// that the supplied base is a power of two, so we call the power2_base function
	    }
	    else{									// if the supplied base is not a power of two, call other_base function
	       other_base(decimal, base);
	    }
	}
	else if (base == 256){						// if supplied base is 256, call base_256 function
	    base_256(decimal, base);
	}
	else{										// show an error if user supplies a base outside of range 
	    printf("INVALID BASE\n");				// of 2-64 and 256
	    return -1;
	}

	// here are two ways to print from certain
	// location in the buffer, use one of them
	// printf("%s\n", buffer + (pointer + 1));

	printf("%s\n", &buffer[pointer + 1]);

	// remember there should only be a SINGLE call
	// to `printf()` in your entire program

	// exit with 0 if the program was successful
	return 0;
}

void other_base(unsigned decimal, unsigned base){

	// TODO: for bases that are not a power of 2 or 256
	int quotient = 1, remainder, x;

	while (quotient != 0){									// continue the algorithm until the division results in 0
	   pointer--;											// decrement the pointer
	   remainder = decimal % base;							// get the remainder 
	   quotient = decimal / base;							// get the quotient 
	// fill the buffer from the end, toward the start
	   for (x=0; ascii[x] != '\0'; x++){
	       if (remainder < 10){								// if remainder is a number between 0 and 9, 
	            if (remainder + 48 == ascii[x]){			// check if it matches the character in ascii array after adding 48 or '0'
	                buffer[pointer + 1] = ascii[x];			// if it's a match, put the corresponding character into the buffer
	            }
	       }
	       else if (remainder > 9 && remainder < 36){		// else if remainder is between 10 and 35 (a character between A - Z),
	           if (remainder + 55 == ascii[x]){				// check if it matches the character in ascii array after adding 55
	               buffer[pointer + 1] = ascii[x];			// if it's a match, put the corresponding character into the buffer
	           }
	       }
	       else{											// else if remainder is more than 35 (a character between a - z),
	           if (remainder + 61 == ascii[x]){				// check if it matches the character in ascii array after adding 61
	               buffer[pointer + 1] = ascii[x];			// if it's a match, put the corresponding character into the buffer
	           }
	       }
	   }
	   decimal = quotient;									// set the new decimal to be the quotient in order to continue the algorithm 
	}
	return;
}

void power2_base(unsigned decimal, unsigned base){

	// TODO: for bases that are a power of 2 but still not 256 
	int mask = base - 1, shift = log2(base), maskedOff, x;

	while (decimal != 0){									// continue the algorithm until the result of right shift is 0
		pointer--;											// decrement the pointer
		maskedOff = decimal & mask;							// use the bitwise AND operator to get the masked off digit

		for (x = 0; ascii[x] != '\0'; x++){					
	       if (maskedOff < 10){								// if masked off digit is a number between 0 and 9,
	            if (maskedOff + 48 == ascii[x]){			// check if it matches the character in ascii array after adding 48 or '0' 
	                buffer[pointer + 1] = ascii[x];			// if it's a match, put the corresponding character into the buffer
	            }
	       }
	       else if (maskedOff > 9 && maskedOff < 36){		// else if masked off digit is between 10 and 35 (a character between A - Z),
	           if (maskedOff + 55 == ascii[x]){				// check if it matches the character in ascii array after adding 55
	               buffer[pointer + 1] = ascii[x];			// if it's a match, put the corresponding character into the buffer
	           }
	       }
	       else{											// else if masked off digit is more than 35 (a character between a - z),
	           if (maskedOff + 61 == ascii[x]){				// check if it matches the character in ascii array after adding 61
	               buffer[pointer + 1] = ascii[x];			// if it's a match, put the corresponding character into the buffer
	           }
	       }
        }	
    	decimal = decimal >> shift;							// shift the bits to the right using the bitwise RIGHT SHIFT operator
	}														// and assign it to the decimal variable  
	return;
}

void base_256(unsigned decimal, unsigned base){
	
	// TODO: for base 256 only
	int mask = base - 1, shift = log2(base), maskedOff, quotient, remainder, x;
	
	while (decimal != 0){									// continue the algorithm until the result of right shift is 0
       	maskedOff = decimal & mask;							// use the bitwise AND operator to get the masked off digit
        quotient = maskedOff;								// set the quotient to be the masked off digit
        
        if (quotient == 0){									// if the quotient is 0,
            pointer--;										// decrement the pointer and append '0' to the buffer 
            buffer[pointer + 1] = '0';   
        }
        
        while (quotient != 0){								// while quotient does not equal to 0,
            pointer--;										// decrement the pointer
            remainder = quotient % 10;						// get last digit by modulo 10 
            quotient = quotient / 10;						// get quotient by dividing 10 (numbers less than 10 will result in 0)
            for (x = 0; ascii[x] != '\0'; x++){				// loop through the number calculated through mask and shift (at most 3 digits)
	            if (remainder + 48 == ascii[x]){			// and place each digit into the buffer
	                buffer[pointer + 1] = ascii[x];
	            }
	            
            }
        }
    
	    decimal = decimal >> shift;							// shift the bits to the right using the bitwise RIGHT SHIFT operator
															// and assign it to the decimal variable  
	    if (decimal != 0){									 
            pointer--;										// if decimal does not equal to zero, decrement the pointer and append '.' 
            buffer[pointer + 1] = '.';						// to the buffer
	    }
	}
	return;
}

