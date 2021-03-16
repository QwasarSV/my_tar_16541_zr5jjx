#include "../my_tar.h"

void	createFromTarHeader(t_MyTarFile *self, my_tar_header *header) {
	// fills out the possix struct
	my_memcpy(self->header, header, sizeof(*header));

	// fills out the file_info struct
	my_strcpy(self->file_info->name, header->name);
	self->file_info->mode = octal_to_decimal(my_atoi(header->mode));
	self->file_info->uid = octal_to_decimal(my_atoi(header->uid));
	self->file_info->gid = octal_to_decimal(my_atoi(header->gid));
	self->file_info->size = octal_to_decimal(my_atoi(header->size));
	self->file_info->mtime = octal_to_decimal(my_atoi(header->mtime));
	self->file_info->chksum = octal_to_decimal(my_atoi(header->chksum));
	self->file_info->typeflag = header->typeflag - '0';
	my_strcpy(self->file_info->linkname, header->linkname);
	my_strcpy(self->file_info->uname, header->uname);
	my_strcpy(self->file_info->gname, header->gname);
	self->file_info->devmajor = octal_to_decimal(my_atoi(header->devmajor));
	self->file_info->devminor = octal_to_decimal(my_atoi(header->devminor));
	my_strcpy(self->file_info->prefix, header->prefix);
}