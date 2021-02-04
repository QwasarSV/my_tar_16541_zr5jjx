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
} my_tar_header;

typedef struct my_tar_options {
	bool create;
	bool extract;
	bool append;
	bool update;
	bool list;
	bool tar_name;
	int error;
} my_tar_options;

typedef struct MyTar {
	MyTarFile *_data;

	void	(*loadFromFileNames)(struct MyTar *self, char **filenames);
	void	(*loadFromArchive)(struct MyTar *self, char *archive_filename);

	void	(*saveToArchive)(struct MyTar *self);
	void	(*extractFiles)(struct MyTar *self);
	void	(*list)(struct MyTar *self);

	void	(*updateFile)(struct MyTar *self, char *filename);
	void	(*appendFile)(struct MyTar *self, char *filename);
} MyTar;

typedef struct MyTarFile {
	my_tar_header	 *header;
	struct MyTarFile *next;
	struct MyTarFile *prev;

	// One of these two functions will be used to create our list of files
	void	(*createFromFilename)(struct MyTarFile *self, char* filename);
	void	(*createFromTarHeader)(struct MyTarFile *self, my_tar_header *header);

	void	(*writeToArchive)(struct MyTarFile *self, int fd_tar_archive);
	int		(*createFile)(struct MyTarFile *self); //returns the file descriptor of the newly created file
}	MyTarFile;

// Functions Used in MyTar
void	loadFromFileNames(struct MyTar *self, char **filenames);
void	loadFromArchive(struct MyTar *self, char *archive_filename);
void	saveToArchive(struct MyTar *self);
void	extractFiles(struct MyTar *self);
void	list(struct MyTar *self);
void	updateFile(struct MyTar *self, char *filename);
void	appendFile(struct MyTar *self, char *filename);

// Functions Used in MyTarFile
void	createFromFilename(struct MyTarFile *self, char* filename);
void	createFromTarHeader(struct MyTarFile *self, my_tar_header *header);
void	writeToArchive(struct MyTarFile *self, int fd_tar_archive);
int		createFile(struct MyTarFile *self); //returns the file descriptor of the newly created file

#endif
