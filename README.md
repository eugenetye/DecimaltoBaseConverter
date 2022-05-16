# Decimal to Base Converter
This is a C program that converts a number from decimal to the user's desired base.

## Project Specifications

This program takes **1)** a number written in decimal and **2)** the base that you want to convert to as *command line arguments* and output the answer. 
All bases from **1)** 2 to 64 and **2)** 256 should be able to be handled by this program. Error messages such as INVALID BASE or INVALID NUMBER should be printed out if the input contains an invalid base (outside the range mentioned above), an invalid number of command line arguments, or a non-number argument.

One of three different functions will be called based on the user's desired base. 
1. For bases that are not a power of 2 or 256, the function `other_base` will be called. Here, a series of division operations is invloved, in which the divisor is always the base. Each time a division is performed the remainder and quotient are saved. The quotient from each step becomes the dividend in the next step. The algorithm stops when the quotient is 0. The representation of the number in the new base is the sequence of the remainders in reverse order.
2. For bases that are a power of 2 but still not 256, the function `power2_base` will be called. This function uses a series of mask and shift oprations. The masking operation uses the bitwise AND operator with the decimal number and the mask value, which is obtained by subtracting 1 from the base value, to get the masked off digit. The second operand of right shift operation is the output of `log2(base)`. The result from each right shift operation becomes the first operand of the masking operation. The algorithm stops when the result of right shift operation is 0. The representation of the number in the new base is the sequence of the masked off digits in reverse order.
3. For bases that are 256, the function `base_256` will be called. Here, mask and shift operations are used together with division operations. The mask and shift operations here are the same as above. Here, the quotient is set to be the masked off digit. If the quotient is 0, `0` is appended to the output. While quotient does not equal to 0, the remainder is obtained by `quotient % 10`, and the result of `quotient / 10` from each step becomes the quotient in the next step. The algorithm stops when the result of right shift is 0. The representation of the number in the new base is the sequence of the remainders in reverse order, in the form of an IP address.


## Makefile

A `Makefile` is provided, simply type `make` to compile the program. You can type `make clean` to remove the compiled program.

## Example Output
![Screen Shot 2022-05-16 at 12 18 04 PM](https://user-images.githubusercontent.com/105037989/168638177-5f227e04-e4f5-4ef1-914f-e19fb03ab098.png)

>The dollar sign is not something you should type, it just represents the prompt in the terminal.

