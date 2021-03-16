#include "../my_tar.h"

void	writeToArchive(t_MyTarFile *self, int fd_tar_archive) {
	char	buf[512] = {0};

	write(fd_tar_archive, self->header, sizeof(*self->header));
	write(fd_tar_archive, buf, 12);
	if (self->file_info->size != 0){
		write(fd_tar_archive, self->file_contents, octal_to_decimal(atoi(self->header->size)));
		write(fd_tar_archive, buf, 512 - self->file_info->size % 512);
	}
}