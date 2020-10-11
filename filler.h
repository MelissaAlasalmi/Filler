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
	int m;
	char **piece;
	int	piece_y;
	int	piece_x;
	int p;
	int y_offset;
    int x_offset;
	int npiece_y;
	int npiece_x;
	int coord_y;
	int coord_x;
	int sum;
}					t_filler;

int		scan_fd(t_filler *data, char *line);
int		construct_map(t_filler *map);
void	prep_piece(t_filler *map);
void 	teststruct(t_filler *data);
void 	testmap(t_filler *data);
void 	testheatmap(t_filler *data);
void 	testpiece(t_filler *data);
void	place_piece(t_filler *data);
void	free_map(t_filler *data);
void	free_piece(t_filler *data);
void	free_heatmap(t_filler *data);

#endif