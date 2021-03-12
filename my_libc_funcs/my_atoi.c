#include "../my_tar.h"

int		my_atoi(char *num) {
	unsigned int result = 0;
	int sign = 1;
	int i = 0;

	if (num[i] == '-') {
		sign *= -1;
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9') {
		result = (num[i] - '0') + result * 10;
		i++;
	}
	return result * sign;
}