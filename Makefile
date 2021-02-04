EXEC = my_tar
FILES = main
SRCS = $(addsuffix .c,$(FILES))
OBJS = $(addsuffix .o,$(notdir $(FILES)))
CFLAGS += -Wall -Wextra -Werror -fsanitize=address

all : EXEC

$(EXEC) : %.o
	gcc $(CFLAGS) -o $(EXEC) $(OBJS)

%.o : %.c
	gcc $(CFLAGS) -c $<

debug : %.o
	gcc $(CFLAGS) -g -o debug $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC) debug

re : fclean all