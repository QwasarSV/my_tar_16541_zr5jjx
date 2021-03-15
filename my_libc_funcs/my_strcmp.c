#include "../my_tar.h"

int		my_strcmp(char *s1, char *s2) {
	int i = 0;

	while (s1[i] && s2[i]) {
		if (s1[i] != s2[i]) {
			return s1[i] - s2[i];
		}
		i++;
	}
	return s1[i] - s2[i];
}