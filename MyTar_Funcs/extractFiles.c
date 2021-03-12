#include "../my_tar.h"

void	extractFiles(t_MyTar *self) {
	t_MyTarFile *temp = self->_data;

	while (temp) {
		temp->createFile(temp);
		temp = temp->next;
	}
}