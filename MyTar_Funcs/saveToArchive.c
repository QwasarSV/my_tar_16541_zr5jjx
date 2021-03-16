#include "../my_tar.h"

void	saveToArchive(t_MyTar *self, char *archive_name) {
	int fd;
	t_MyTarFile *temp = self->_data;
	char buf[1024] = {0};

	fd = open(archive_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (temp) {
		writeToArchive(temp, fd);
		temp = temp->next;
	}
	write(fd, buf, 1024);
	close(fd);
}