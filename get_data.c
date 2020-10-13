#include "filler.h"

int scan_fd(t_filler *data, char *line, int p)
{
	char **coord;
	int y;

	coord = NULL;
	y = 0;
	if (line && ft_strstr(line, "Plateau"))
	{
		if (!(coord = ft_strsplit(&line[7], ' ')))
			return (1);
		data->map_y = ft_atoi(coord[0]);
		data->map_x = ft_atoi(coord[1]);
		if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y)))
			return (1);
		while (y < data->map_y)
		{
			if(!(data->map[y] = (char*)malloc(sizeof(char) * data->map_x)))
				return(1);
			y++;
		}
		free(coord);
	}
	else if (line[0] == '0')
	{
		data->map[data->m] = ft_strdup(&line[4]);
		data->m++;
		if (data->m == data->map_y)
		{
			if (construct_map(data, p) == 1)
				return (1);
			data->m = 0;
			free_map(data);
		}
	}
	else if (ft_strstr(line, "Piece"))
	{
		if (!(coord = ft_strsplit(&line[5], ' ')))
			return (1);
		data->piece_y = ft_atoi(coord[0]);
		data->piece_x = ft_atoi(coord[1]);
		if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y)))
			return (1);
		while (y < data->piece_y)
		{
			if(!(data->piece[y] = (char*)malloc(sizeof(char) * data->piece_x)))
				return(1);
			y++;
		}
		free(coord);
	}
	else if (line && (line[0] == '.' || line[0] == '*'))
	{
		data->piece[data->p] = ft_strdup(line);
		data->p++;
	}
	if (data->p != 0 && data->p == data->piece_y)
	{
		prep_piece(data);
		place_piece(data);
		ft_putnbr(data->coord_y - data->y_offset);
		ft_putchar(' ');
		ft_putnbr(data->coord_x - data->x_offset);
		ft_putchar('\n');
		return(2);
	}
	return (0);
}