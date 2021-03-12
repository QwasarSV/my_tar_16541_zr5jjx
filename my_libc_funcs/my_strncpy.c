#include "../my_tar.h"

char*	my_strncpy(char *dest, char *src, int n) {
	for (int i = 0; i < n; i++) {
		dest[i] = src[i];
	}
	return dest;
}