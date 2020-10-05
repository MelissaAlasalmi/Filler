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
	char **piece;
	int	piece_y;
	int	piece_x;
	int y_offset;
    int x_offset;
	int npiece_y;
	int npiece_x;
	int coord_y;
	int coord_x;
	int sum;
}					t_filler;

int construct_map(t_filler *map);
void prep_piece(t_filler *map);
int teststruct(int power, t_filler *data);
void place_piece(t_filler *data);

#endif