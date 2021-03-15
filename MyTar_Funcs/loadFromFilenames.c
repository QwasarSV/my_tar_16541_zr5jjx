#include "../my_tar.h"

void	loadFromFilenames(t_MyTar *self, char **filenames, int file_count) {
	t_MyTarFile	*cur;
	t_MyTarFile	*prev = NULL;
	int			i = 0;

	self->_data = my_tar_file_init();
	cur = self->_data;
	while (i < file_count) {
		cur->prev = prev;
		cur->createFromFilename(cur, filenames[i]);
		if (cur->file_info->typeflag == 5) {
			load_directory(cur->file_info->name, self);
		}
		if (i < file_count - 1) {
			cur->next = my_tar_file_init();
		}
		prev = cur;
		cur = cur->next;
		i++;
	}
}