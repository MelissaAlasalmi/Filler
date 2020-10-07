NAME = malasalm.filler

SRCS = 	main.c get_data.c construct_map.c prep_piece.c place_piece.c teststruct.c free_helpers.c \

OBJS = 	main.o get_data.o construct_map.o prep_piece.o place_piece.o teststruct.o free_helpers.o \

INCS = -I libft/libft.h

HEADER = filler.h

CFLAGS = -Wall -Wextra -Werror

LIB = -L libft -lft

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -g -c $(SRCS) $(INCS)
	gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all