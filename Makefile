NAME = malasalm.filler

SRCS = 	srcs/main.c srcs/get_data.c srcs/construct_map.c srcs/prep_piece.c srcs/place_piece.c srcs/free_helpers.c \

OBJS = 	main.o get_data.o construct_map.o prep_piece.o place_piece.o free_helpers.o \

INCS = -I libft/libft.h

HEADER = filler.h

CFLAGS = -Wall -Wextra -Werror

LIB = -L libft -lft

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc $(CFLAGS) -g -c $(SRCS) $(INCS)
	@gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)
	@mkdir objs 
	@mv $(OBJS) objs 

.PHONY: clean fclean re all

clean:
	rm -rf objs
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all