#include "../my_tar.h"

static void	c_regtype_file(t_MyTarFile *self); 
static void c_dirtype_file(t_MyTarFile *self);
static void	c_lnktype_file(t_MyTarFile *self);
static void	c_symtype_file(t_MyTarFile *self);

// returns fd of newly created file
//chaning return to void
void	createFile(t_MyTarFile *self) {
	int filetype = self->header->typeflag;

	switch (filetype) {
		case  '0':
			c_regtype_file(self);
			break;
		case '1':
			c_lnktype_file(self);
			break;
		case '2':
			c_symtype_file(self);
			break;
		case '5':
			c_dirtype_file(self);
			break;
		default:
			printf("Error: Invalid filetype for file: %s\nCould not extract...", self->file_info->name);
			break;
	}

	// since I have to return fd I'm assuming that means I can't close the file here.
	// I have to close the file outside of this function?
	// Making executive decision to not return here as I don't understand how it
	// accomplishes anything
}

static void	c_regtype_file(t_MyTarFile *self) {
	int	fd;
	struct utimbuf times;
	char *filename = self->file_info->name;
	
	time(&times.actime);
	times.modtime = self->file_info->mtime;
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY);
	chmod(filename, self->file_info->mode);
	utime(filename, &times);
	write(fd, self->file_contents, self->file_info->size);
	close(fd);
}

static void	c_lnktype_file(t_MyTarFile *self) {
	link(self->file_info->name, self->file_info->linkname);
}

static void	c_symtype_file(t_MyTarFile *self) {
	symlink(self->file_info->linkname, self->file_info->name);
}

static void c_dirtype_file(t_MyTarFile *self) {
	mkdir(self->file_info->name, self->file_info->mode);
}