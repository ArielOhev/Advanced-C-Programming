#include <stdio.h>
#include <string.h>

int quest1(int num, int count);
int quest2(int num, int count);
void displayBits(int value);

int main() {
    
    int val = 0x19337EE6; // 00011001 00110011 01111110 11100110
    int shift = 8;

    printf("Original number:\n");
    displayBits(val);

    printf("\nAfter Circular Left Shift by %d:\n", shift);
    int left_shifted = quest1(val, shift);
    displayBits(left_shifted);

    printf("\nAfter Circular Right Shift by %d:\n", shift);
    int right_shifted = quest2(val, shift);
    displayBits(right_shifted);

    return 0;


    return 0;
}

int quest1(int num, int count) {
    unsigned int new_num = num << count;
	unsigned int temp = num >> (32 - count);

	return (int)(new_num | temp);
}

int quest2(int num, int count) {
    unsigned int new_num = num >> count;
    unsigned int temp = num << (32 - count);
    return (int)(new_num | temp);
}

void displayBits(int value)
{
	unsigned c;
	unsigned displayMask = 1 << 31;

	printf("%7d = ", value);
	for (c = 1; c <= 32; c++) {
		putchar(value & displayMask ? '1' : '0');
		value <<= 1;
		if (c % 8 == 0) {
			putchar(' ');
		}
	}

	putchar('\n');
}