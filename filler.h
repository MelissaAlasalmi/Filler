#ifndef FILLER_H
# define FILLER_H
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h> // REMOVE!

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
	int row_offset;
    int column_offset;
	int **npiece;
}					t_filler;

int construct_map(t_filler *map);
void place_piece(t_filler *map);
int teststruct(int power, t_filler *data);
// void return_coordnates(t_filler *map);

#endif