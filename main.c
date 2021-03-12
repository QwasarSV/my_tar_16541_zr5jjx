/*
#TODO Create TODO List --Completed
#TODO Handle Directories
#TODO Handle symbolic links --Completed
#TODO Handle hard links --Having trouble figuring this one out
#TODO Create Parsing Function
#TODO Create List Method --Completed
#TODO Create Append Method
#TODO Create Update Method
#TODO Revamp Functional Tests
*/


#include "my_tar.h"

static void	direct_to_functions(t_my_tar_options options, char **files, int size);

int		main(int ac, char **av) {
	t_my_tar_options options;

	if (ac < 3) {
		printf("tar: You must specify one of the '-ctrux' options\n");
		return 0;
	}
	options = parse_options(&av[1], ac - 1);
	direct_to_functions(options, &av[1], ac - 1);
	return 0;
}

static void	direct_to_functions(t_my_tar_options options, char **files, int size) {
	t_MyTar *MyTar = my_tar_init();

	while (size) {
		if (files[0][0] == '-') {
			files++;
		}
		else {
			break;
		}
		size--;
	}
	if ((options.flags & CREATE) == CREATE) {
		MyTar->loadFromFilenames(MyTar, &files[1], size - 1);
		MyTar->saveToArchive(MyTar, files[0]);
	}
	else if ((options.flags & EXTRACT) == EXTRACT) {
		MyTar->loadFromArchive(MyTar, files[0]);
		MyTar->extractFiles(MyTar); // May need to change to extract specific files
	}
	else if ((options.flags & APPEND) == APPEND) {
		MyTar->loadFromArchive(MyTar, files[0]);
		for (int i = 1; i < size; i++) {
			MyTar->appendFile(MyTar, files[i]);
		}
		MyTar->saveToArchive(MyTar, files[0]);
	}
	else if ((options.flags & UPDATE) == UPDATE) {
		MyTar->loadFromArchive(MyTar, files[0]);
		for (int i = 1; i < size; i++) {
			MyTar->updateFile(MyTar, files[i]);
		}
		MyTar->saveToArchive(MyTar, files[0]);
	}
	else if ((options.flags & LIST) == LIST) {
		MyTar->loadFromArchive(MyTar, files[0]);
		MyTar->list(MyTar);
	}
	else {
		printf("Unrecognized flag, should have been caught prior to this check\n");
		return;
	}

	MyTar->freeAll(MyTar);
}