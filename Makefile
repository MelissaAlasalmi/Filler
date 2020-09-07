NAME = malasalm.filler

SRCS = 	filler.c \

OBJS = 	filler.o \

INCS = -I libft/libft.h

HEADER = filler.h

CFLAGS = -Wall -Wextra -Werror

LIB = -L libft -lft

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -c $(SRCS) $(INCS)
	gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all