#include "../my_tar.h"

static int	file_exists(char *file);

void	loadFromFilenames(t_MyTar *self, char **filenames, int file_count) {
	t_MyTarFile	*cur;
	t_MyTarFile	*prev = NULL;
	int			i = 0;

	self->_data = my_tar_file_init();
	cur = self->_data;
	while (i < file_count) {
		if (file_exists(filenames[i]) == -1) {
			printf("tar: %s: Cannot stat: No such file or directory\n", filenames[i]);
			i++;
			continue;
		}
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

static int	file_exists(char *file) {
	struct stat sb;

	return stat(file, &sb);
}