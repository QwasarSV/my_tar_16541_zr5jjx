#include "../my_tar.h"

static int	advance_to_next_header(int fd, int last_file_size);

void	loadFromArchive(t_MyTar *self, char *archive_filename) {
	int				fd;
	my_tar_header	header;
	t_MyTarFile		**temp = &self->_data;

	fd = open(archive_filename, O_RDONLY);
	*temp = my_tar_file_init();
	while (*temp && read(fd, &header, 500) > 0) {
		lseek(fd, 12, SEEK_CUR);
		(*temp)->createFromTarHeader(*temp, &header);
		(*temp)->file_contents = (char*)malloc((*temp)->file_info->size + 1);
		read(fd, (*temp)->file_contents, (*temp)->file_info->size);
		(*temp)->file_contents[(*temp)->file_info->size] = '\0';
		if (advance_to_next_header(fd, (*temp)->file_info->size) == 0) {
			(*temp)->next = my_tar_file_init();
		}
		temp = &(*temp)->next;
	}
	close(fd);
}

// advances the file pointer through the file contents
// and to the beginning of the next archived member
// returns 1 upon reaching EOF 0 if it finds another member
static int	advance_to_next_header(int fd, int last_file_size) {
	char	buf[512];
	int		offset = 0;

	if (last_file_size % 512 > 0) {
		offset = 512 - (last_file_size % 512);
	}
	lseek(fd, offset, SEEK_CUR);
	read(fd, buf, 512);
	if (buf[0] > 0) {
		lseek(fd, -512, SEEK_CUR);
		return 0;
	}
	return 1;
}