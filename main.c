#include "my_tar.h"

// Should I malloc this? thinking no since I'll only ever need one of them
// but maybe safer to do so, and if I only need one it's easy to keep track of
// right?
MyTar	my_tar_init() {
	MyTar MyTar = {
		._data = NULL,
		.loadFromFileNames = &loadFromFileNames,
		.loadFromArchive = &loadFromArchive,
		.saveToArchive = &saveToArchive,
		.extractFiles = &extractFiles,
		.list = &list,
		.updateFile = &updateFile,
		.appendFile = &appendFile
	};
	return MyTar;
}

// Should I malloc this? probably need to since it will
// be a node in a linked list I don't want data to get
// written over it.
MyTarFile	my_tar_file_init() {
	MyTarFile MyTarFile = {
		.header = NULL,
		.next = NULL,
		.prev = NULL,
		.createFromFilename = &createFromFilename,
		.createFromTarHeader = &createFromTarHeader,
		.writeToArchive = &writeToArchive,
		.createFile = &createFile
	};
	return MyTarFile;
}