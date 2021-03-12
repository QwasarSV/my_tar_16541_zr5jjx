#include "my_tar.h"

t_MyTar*	my_tar_init() {
	t_MyTar *MyTar;

	MyTar = (t_MyTar*)malloc(sizeof(t_MyTar));

	MyTar->_data = NULL;
	MyTar->loadFromFilenames = &loadFromFilenames;
	MyTar->loadFromArchive = &loadFromArchive;
	MyTar->saveToArchive = &saveToArchive;
	MyTar->extractFiles = &extractFiles;
	MyTar->list = &list;
	MyTar->updateFile = &updateFile;
	MyTar->appendFile = &appendFile;
	MyTar->freeAll = &freeAll;

	return MyTar;
}