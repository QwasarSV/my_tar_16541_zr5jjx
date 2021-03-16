#include "../my_tar.h"

void*	my_memset(void *s, int val, size_t n) {
	char *temp = s;

	while (n--) {
		temp[n] = val;
	}
	return s;
}