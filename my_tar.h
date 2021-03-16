#ifndef MY_TAR_H
#define MY_TAR_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <time.h>
#include <utime.h>
#include <stdbool.h>
#include <sys/sysmacros.h>

// Flags for different operating modes
#define CREATE		0b00000001
#define EXTRACT		0b00000010
#define APPEND		0b00000100
#define UPDATE		0b00001000
#define LIST		0b00010000

// Error Codes
#define UNKNOWN_OPTION 1
#define MULTIPLE_OPTIONS 2
#define MISSING_ARCHIVE 3

// STRUCTS // --------------------------------------------------------------

typedef struct my_tar_header {
	char name[100];               /*   0 */
	char mode[8];                 /* 100 */
	char uid[8];                  /* 108 */
	char gid[8];                  /* 116 */
	char size[12];                /* 124 */
	char mtime[12];               /* 136 */
	char chksum[8];               /* 148 */
	char typeflag;                /* 156 */
	char linkname[100];           /* 157 */
	char magic[6];                /* 257 */
	char version[2];              /* 263 */
	char uname[32];               /* 265 */
	char gname[32];               /* 297 */
	char devmajor[8];             /* 329 */
	char devminor[8];             /* 337 */
	char prefix[155];             /* 345 */
								  /* 500 */
}	my_tar_header;

typedef struct s_file_info{
	char	name[100];
	int		mode;
	int		uid;
	int		gid;
	int		size;
	int		mtime;
	int		chksum;
	char	typeflag;
	char	linkname[100];
	char	uname[32];
	char	gname[32];
	int		devmajor;
	int		devminor;
	char	prefix[155];
}	t_file_info;

typedef struct s_my_tar_options {
	int flags;
	bool tar_file;
	int error;
}	t_my_tar_options;

// class which contains the functions necessary to execute tar commands
typedef struct s_MyTar {
	struct s_MyTarFile *_data;

	void	(*loadFromFilenames)(struct s_MyTar *self, char **filenames, int file_count);
	void	(*loadFromArchive)(struct s_MyTar *self, char *archive_filename);

	void	(*saveToArchive)(struct s_MyTar *self, char *archive_name);
	void	(*extractFiles)(struct s_MyTar *self);
	void	(*list)(struct s_MyTar *self);
	void	(*updateFile)(struct s_MyTar *self, char *filename);
	void	(*appendFile)(struct s_MyTar *self, char *filename);

	void	(*freeAll)(struct s_MyTar *self);
}	t_MyTar;

// linked list for storing each file information
typedef struct s_MyTarFile {
	my_tar_header	*header;
	t_file_info		*file_info;
	char			*file_contents;
	struct s_MyTarFile *next;
	struct s_MyTarFile *prev;

	// One of these two functions will be used to create our list of files
	void	(*createFromFilename)(struct s_MyTarFile *self, char* filename);
	void	(*createFromTarHeader)(struct s_MyTarFile *self, my_tar_header *header);

	void	(*writeToArchive)(struct s_MyTarFile *self, int fd_tar_archive);
	void	(*createFile)(struct s_MyTarFile *self); //returns the file descriptor of the newly created file
}	t_MyTarFile;

// END STRUCTS //---------------------------------------------------------------------------


// Functions Used in MyTar
void	loadFromFilenames(struct s_MyTar *self, char **filenames, int file_count);
void	loadFromArchive(struct s_MyTar *self, char *archive_filename);
void	saveToArchive(struct s_MyTar *self, char *archive_name);
void	extractFiles(struct s_MyTar *self);
void	list(struct s_MyTar *self);
void	updateFile(struct s_MyTar *self, char *filename);
void	appendFile(struct s_MyTar *self, char *filename);
void	freeAll(struct s_MyTar *self);

// Functions Used in MyTarFile
void	createFromFilename(struct s_MyTarFile *self, char* filename);
void	createFromTarHeader(struct s_MyTarFile *self, my_tar_header *header);
void	writeToArchive(struct s_MyTarFile *self, int fd_tar_archive);
void	createFile(struct s_MyTarFile *self); //returns the file descriptor of the newly created file


t_MyTar*			my_tar_init();
t_MyTarFile*		my_tar_file_init();
int					octal_to_decimal(long octal_num);
t_my_tar_options	parse_options(char **command, int size);
void				load_directory(char *dir_name, t_MyTar *self);

// Recreations of library functions
char*	my_strcpy(char *dest, char *src);
char*	my_strcat(char *dest, char *src);
int		my_strcmp(char *s1, char *s2);
long	my_atoi(char *nbr);
char*	my_itoa(int value, char* dest, int base);
void	my_strrev(char *str);
void*	my_memset(void *s, int val, size_t n);
int		my_strlen(char *str);
void*	my_memcpy(void *dest, void *src, size_t n);
char*	my_strncpy(char *dest, char *src, int n);

#endif
