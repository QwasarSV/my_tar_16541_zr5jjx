#include "../my_tar.h"

void	updateFile(t_MyTar *self, char *filename) {
	struct stat statbuf;
	t_MyTarFile *temp = self->_data;

	if (stat(filename, &statbuf) == -1) {
		printf("tar: %s: Cannot stat: No such file or directory\n", filename);
	}
	while (temp) {
		if (my_strcmp(temp->file_info->name, filename) == 0 &&
				temp->file_info->mtime >= statbuf.st_mtim.tv_sec) {
			return ;
		}
		temp = temp->next;
	}
	appendFile(self, filename);
}