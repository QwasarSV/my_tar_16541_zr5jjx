#include "../my_tar.h"

static void	free_data(t_MyTarFile *self);

void	freeAll(t_MyTar *self) {
	free_data(self->_data);
	free(self);
}

static void	free_data(t_MyTarFile *self) {
	if (!self) {
		return ;
	}
	if (self->next) {
		free_data(self->next);
	}
	if (self->file_contents) {
		free(self->file_contents);
	}
	free(self->header);
	free(self->file_info);
	free(self);
}