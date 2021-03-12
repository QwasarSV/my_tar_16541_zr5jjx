#include "../my_tar.h"

static void			tar_header_from_file_info(my_tar_header *header, t_file_info *file_info);
static void			file_info_from_file(t_file_info *file_info, char *filename);
static unsigned int	calculate_chksum(my_tar_header *header);
char*				copy_file(char *filename, size_t size);
static char*		format(char *dest, char *str, int size);
static char*		get_gname(gid_t id);
static char*		get_uname(uid_t id);
static int			determine_filetype(char *filename);

void	createFromFilename(t_MyTarFile *self, char *filename) {
	char format_buf[100];
	char buf[20];

	file_info_from_file(self->file_info, filename);
	tar_header_from_file_info(self->header, self->file_info);
	self->file_info->chksum = calculate_chksum(self->header);
	my_strcpy(self->header->chksum, format(format_buf, my_itoa(self->file_info->chksum, buf, 8), 7));
	self->header->chksum[6] = '\0';

	self->file_contents = copy_file(filename, self->file_info->size);
}

static void	tar_header_from_file_info(my_tar_header *header, t_file_info *file_info) {
	char buf[20];
	char format_buf[100];

	my_strcpy(header->name, file_info->name);
	my_strcpy(header->mode, format(format_buf, my_itoa(file_info->mode % 01000, buf, 8), 8));
	my_strcpy(header->uid, format(format_buf, my_itoa(file_info->uid, buf, 8), 8));
	my_strcpy(header->gid, format(format_buf, my_itoa(file_info->gid, buf, 8), 8));
	my_strcpy(header->size, format(format_buf, my_itoa(file_info->size, buf, 8), 12));
	my_strcpy(header->mtime, format(format_buf, my_itoa(file_info->mtime, buf, 8), 12));
	my_strcpy(header->chksum, "        "); //when chksum is calculated is counts itself as spaces
	header->typeflag = file_info->typeflag + '0';
	my_strcpy(header->linkname, file_info->linkname);
	my_strcpy(header->magic, "ustar ");
	my_strcpy(header->version, " ");
	my_strcpy(header->uname, file_info->uname); 
	my_strcpy(header->gname, file_info->gname);
	// devmajor and devminor are only present in the case that the fileype is a block file
	if (determine_filetype(file_info->name) == 4) {
		my_strcpy(header->devmajor, format(format_buf, my_itoa(file_info->devmajor, buf, 8), 8));
		my_strcpy(header->devminor, format(format_buf, my_itoa(file_info->devminor, buf, 8), 8));
	}

}

static void	file_info_from_file(t_file_info *file_info, char *filename) {
	struct stat statbuf;

	lstat(filename, &statbuf);
	my_strncpy(file_info->name, filename, 100);
	file_info->mode = statbuf.st_mode;
	file_info->uid = statbuf.st_uid;
	file_info->gid = statbuf.st_gid;
	file_info->size = statbuf.st_size;
	file_info->mtime = statbuf.st_mtime;
	file_info->typeflag = determine_filetype(filename);
	if (file_info->typeflag == 2) {
		readlink(filename, file_info->linkname, 100);
		file_info->size = 0;
	}
	if (file_info->typeflag == 5) {
		file_info->size = 0;
	}
	my_strcpy(file_info->uname, get_uname(statbuf.st_uid));
	my_strcpy(file_info->gname, get_gname(statbuf.st_gid));
	file_info->devmajor = major(statbuf.st_dev);
	file_info->devminor = minor(statbuf.st_dev);
	if (my_strlen(filename) > 100) {
		my_strncpy(file_info->prefix, &filename[99], 100);
	}
}

// In the possix header, if the number doesn't take up the alloted
// space, it is prefixed with zeros. This function will return a string
// with the zeros prefixed so it is formatted properly for the header.
static char*	format(char *dest, char *str, int size) {
	int str_size;
	unsigned int i = 0;

	str_size = my_strlen(str) + 1;
	my_memset(dest, 0, 100);
	while (str_size++ < size) {
		dest[i++] = '0';
	}
	my_strcpy(&dest[i], str);
	return dest;
}

char*	copy_file(char *filename, size_t size) {
	char	*buf;
	int		fd;

	buf = (char*)malloc(size + 1);
	fd = open(filename, O_RDONLY);
	read(fd, buf, size);
	buf[size] = '\0';
	close(fd);
	return buf;
}

static unsigned int		calculate_chksum(my_tar_header *header) {
	unsigned int i = 0;
	char *ptr = (char*)header;
	int sum = 0;

	while (i < 499) {
		sum += ptr[i++];
	}
	return sum;
}

static char*	get_uname(uid_t id) {
	struct passwd *result;

	result = getpwuid(id);
	return result->pw_name;
}

static char*	get_gname(gid_t id) {
	struct group *result;

	result = getgrgid(id);
	return result->gr_name;
}

static int	determine_filetype(char *filename) {
	struct stat sb;

	lstat(filename, &sb);
	if (S_ISREG(sb.st_mode)) {
		return 0;
	}
	if (sb.st_nlink > 1) {
		return 1;
	}
	if (S_ISLNK(sb.st_mode)) {
		return 2;
	}
	if (S_ISCHR(sb.st_mode)) {
		return 3;
	}
	if (S_ISBLK(sb.st_mode)) {
		return 4;
	}
	if (S_ISDIR(sb.st_mode)) {
		return 5;
	}
	if (S_ISFIFO(sb.st_mode)) {
		return 6;
	}
	printf("Error determining filetype of: %s\n", filename);
	return -1;
}