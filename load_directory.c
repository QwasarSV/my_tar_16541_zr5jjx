#include "my_tar.h"

void	load_directory(char *dir_name, t_MyTar *self) {
	DIR *stream;
	struct dirent *file;

	stream = opendir(dir_name);
	while ((file = readdir(stream))) {
		appendFile(self, file->d_name);
	}
	closedir(stream);
}