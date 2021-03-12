#include "../my_tar.h"

void	appendFile(t_MyTar *self, char *filename) {
	t_MyTarFile *temp = self->_data;

	while (temp->next) {
		temp = temp->next;
	}
	temp->next = my_tar_file_init();
	temp->next->prev = temp;
	temp->next->createFromFilename(temp->next, filename);
	if (temp->next->file_info->typeflag == 5) {
		load_directory(temp->next->file_info->name, self);
	}
}