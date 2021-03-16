#include "my_tar.h"

static t_my_tar_options get_options(char **command, int size);
static t_my_tar_options	check_flags(t_my_tar_options options);
static void	error_output(t_my_tar_options options);

t_my_tar_options	parse_options(char **command, int size) {
	t_my_tar_options options;

	options = get_options(command, size);
	if (options.error > 0) {
		error_output(options);
	}
	return options;
}

static t_my_tar_options get_options(char **command, int size) {
	t_my_tar_options options;
	int flags = 0;

	options.error = 0;
	options.tar_file = false;
	for (int i = 0; i < size && command[i][0] == '-'; i++) {
		for (int j = 1; command[i][j]; j++) {
			switch (command[i][j]) {
				case 'c':
					flags = flags | CREATE;
					break;
				case 'x':
					flags = flags | EXTRACT;
					break;
				case 'r':
					flags = flags | APPEND;
					break;
				case 'u':
					flags = flags | UPDATE;
					break;
				case 't':
					flags = flags | LIST;
					break;
				case 'f':
					options.tar_file = true;
					break;
				default:
					options.error = UNKNOWN_OPTION;
					return options;
			}
			options.flags = flags;
		}
	}
	return check_flags(options);
}

static t_my_tar_options	check_flags(t_my_tar_options options) {
	int flags = options.flags;

	if ((flags & CREATE) == CREATE) {
		if (flags > CREATE) {
			options.error = MULTIPLE_OPTIONS;
		}
		else if (options.tar_file == false) {
			options.error = MISSING_ARCHIVE;
		}
		return options;
	}

	if ((flags & EXTRACT) == EXTRACT) {
		if (flags > EXTRACT) {
			options.error = MULTIPLE_OPTIONS;
		}
		else if (options.tar_file == false) {
			options.error = MISSING_ARCHIVE;
		}
		return options;
	}

	if ((flags & APPEND) == APPEND) {
		if (flags > APPEND) {
			options.error = MULTIPLE_OPTIONS;
		}
		else if (options.tar_file == false) {
			options.error = MISSING_ARCHIVE;
		}
		return options;
	}

	if ((flags & UPDATE) == UPDATE) {
		if (flags > UPDATE) {
			options.error = MULTIPLE_OPTIONS;
		}
		else if (options.tar_file == false) {
			options.error = MISSING_ARCHIVE;
		}
		return options;
	}

	if ((flags & LIST) == LIST) {
		if (flags > LIST) {
			options.error = MULTIPLE_OPTIONS;
		}
		else if (options.tar_file == false) {
			options.error = MISSING_ARCHIVE;
		}
		return options;
	}

	else {
		options.error = MULTIPLE_OPTIONS;
		return options;
	}
}

static void error_output(t_my_tar_options options) {
	if (options.error == UNKNOWN_OPTION) {
		printf("my_tar: You must specify one of the '-ctrux' options\n");
	}
	if (options.error == MULTIPLE_OPTIONS) {
		printf("my_tar: You may not specify more than one '-ctrux' option\n");
	}
	if (options.error == MISSING_ARCHIVE) {
		printf("my_tar: Refusing to write archive contents to terminal (missing -f option?)\n");
	}
}