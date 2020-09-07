#ifndef FILLER_H
# define FILLER_H
#include "libft/libft.h"
#include <fcntl.h>

typedef struct	s_coordinates
{
	int	x;
	int	y;
}				t_coordinates;

typedef struct		s_map
{
	char **map;
	int	x;
	int	y;
	int p1_x;
	int p1_y;
	int p2_x;
	int p2_y;
}					t_map;

typedef struct		s_piece
{
	char **piece;
	int	x;
	int	y;
}					t_piece;

typedef struct		s_players
{
	int playernum;
}					t_players;

#endif