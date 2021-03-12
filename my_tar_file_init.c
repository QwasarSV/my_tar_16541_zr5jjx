#include "my_tar.h"

t_MyTarFile*	my_tar_file_init() {
	t_MyTarFile *new;

	new = (t_MyTarFile*)malloc(sizeof(t_MyTarFile));
	new->createFile = &createFile;
	new->createFromFilename = &createFromFilename;
	new->createFromTarHeader = &createFromTarHeader;
	new->writeToArchive = &writeToArchive;
	new->file_contents = NULL;
	new->file_info = NULL;
	new->header = NULL;
	new->next = NULL;
	new->prev = NULL;

	return new;
}