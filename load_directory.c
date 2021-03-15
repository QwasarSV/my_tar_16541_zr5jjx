#include "my_tar.h"

static char*	create_path(char *file, char *dir, char *path);

void	load_directory(char *dir_name, t_MyTar *self) {
	DIR *stream;
	struct dirent *file;
	char path[100];

	stream = opendir(dir_name);
	while ((file = readdir(stream))) {
		if (my_strcmp(".", file->d_name) == 0 || my_strcmp("..", file->d_name) == 0) {
				continue;
		}
		create_path(file->d_name, dir_name, path);
		appendFile(self, path);
	}
	closedir(stream);
}

static char*	create_path(char *file, char *dir, char *path) {
	int len = my_strlen(dir);

	my_strcpy(path, dir);
	if (path[len - 1] != '/') {
		path[len - 1] = '/';
		path[len] = '\0';
	}
	my_strcat(path, file);
	return path;
}