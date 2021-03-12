#include "my_tar.h"

int		octal_to_decimal(int octal_num) {
	int decimal = 0;
	int i = 1;

	while (octal_num != 0) {
		decimal += (octal_num % 10) * i;
		octal_num /= 10;
		i *= 8;
	}
	return decimal;
}