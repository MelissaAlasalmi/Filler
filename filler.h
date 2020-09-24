#ifndef FILLER_H
# define FILLER_H
#include "libft/libft.h"
#include <fcntl.h>

typedef struct		s_filler
{
	int playernum;
	char **map;
	int **heatmap;
	int	map_y;
	int map_x;
	int p1_y;
	int p1_x;
	int p2_y;
	int p2_x;
	char **piece;
	int	piece_y;
	int	piece_x;
}					t_filler;

int construct_map(t_filler *map);
// void return_coordnates(t_filler *map);

#endif