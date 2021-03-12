#include "../my_tar.h"

void	list(t_MyTar *self) {
	t_MyTarFile *temp = self->_data;

	while (temp) {
		printf("%s\n", temp->file_info->name);
		temp = temp->next;
	}
}