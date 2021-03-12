#include "../my_tar.h"

char*	my_strcat(char *dest, char *src) {
	int len = my_strlen(dest);
	my_strcpy(&dest[len], src);
	return dest;
}