#include "../my_tar.h"

// To be noted this itoa won't handle a base larger than 10
// I opted not to include that since it's unnecessary for this project
char*	my_itoa(int value, char *dest, int base) {
	int i = 0;
	while (value) {
		dest[i++] = value % base + '0';
		value /= base;
	}
	dest[i] = '\0';
	my_strrev(dest);
	return dest;
}