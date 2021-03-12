EXEC = my_tar
FILES = main octal_to_decimal my_tar_init my_tar_file_init parse_options \
		load_directory \
		MyTar_Funcs/loadFromFilenames MyTar_Funcs/saveToArchive \
		MyTar_Funcs/freeAll MyTar_Funcs/loadFromArchive MyTar_Funcs/extractFiles \
		MyTar_Funcs/list MyTar_Funcs/appendFile MyTar_Funcs/updateFile \
		MyTarFile_Funcs/createFromFilename MyTarFile_Funcs/writeToArchive \
		MyTarFile_Funcs/createFromTarHeader MyTarFile_Funcs/createFile \
		my_libc_funcs/my_atoi my_libc_funcs/my_itoa my_libc_funcs/my_memset \
		my_libc_funcs/my_strcpy my_libc_funcs/my_strrev my_libc_funcs/my_strlen \
		my_libc_funcs/my_memcpy my_libc_funcs/my_strncpy my_libc_funcs/my_strcat \
		my_libc_funcs/my_strcmp

SRCS = $(addsuffix .c,$(FILES))
OBJS = $(addsuffix .o,$(FILES))
ROOT_OBJS = $(notdir $(OBJS))
CFLAGS += -Wall -Wextra -Werror -fsanitize=address

all : $(EXEC)

$(EXEC) : $(OBJS)
	gcc $(CFLAGS) -o $(EXEC) $(ROOT_OBJS)

%.o : %.c
	gcc $(CFLAGS) -c $<

debug :
	gcc $(CFLAGS) -g -o debug $(SRCS)

clean :
	rm -rf $(ROOT_OBJS)

fclean : clean
	rm -rf $(EXEC) debug archive.tar

re : fclean all

rebug : fclean debug