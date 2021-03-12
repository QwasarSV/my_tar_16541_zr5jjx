#include "../my_tar.h"

void*	my_memcpy(void *dest, void *src, size_t n) {
	char *temp_dest = dest;
	char *temp_src = src;

	for (unsigned int i = 0; i < n; i++) {
		temp_dest[i] = temp_src[i];
	}
	return dest;
}