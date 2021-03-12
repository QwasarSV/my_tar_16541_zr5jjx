#include "../my_tar.h"

void	my_strrev(char *str) {
	char temp;
	int start = 0;
	int end = my_strlen(str) - 1;

	while (start < end) {
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		end--;
		start++;
	}
}