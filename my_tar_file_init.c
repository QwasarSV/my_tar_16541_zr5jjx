#include "my_tar.h"

t_MyTarFile*	my_tar_file_init() {
	t_MyTarFile *new;

	new = (t_MyTarFile*)malloc(sizeof(t_MyTarFile));
	new->createFile = &createFile;
	new->createFromFilename = &createFromFilename;
	new->createFromTarHeader = &createFromTarHeader;
	new->writeToArchive = &writeToArchive;
	new->file_info = (t_file_info*)malloc(sizeof(t_file_info));
	new->header = (my_tar_header*)malloc(sizeof(my_tar_header));
	my_memset(new->header, 0, 500);
	new->file_contents = NULL;
	new->next = NULL;
	new->prev = NULL;

	return new;
}