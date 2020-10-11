#include "filler.h"

int scan_fd(t_filler *data, char *line)
{
	int x;
	int i;
	int j;
	
	x = 0;
	// ft_putstr_fd("line in scan: ", 2);
	// ft_putstr_fd(line, 2);
	// ft_putchar_fd('\n', 2);
	if (line && ft_strstr(line, "$$$"))
		data->playernum = ft_atoi(&line[10]);
	else if (line && ft_strstr(line, "Plateau"))
	{
		data->map_y = ft_atoi(line);
		while (line && *line != ' ')
			line++;
		line++;
		data->map_x = ft_atoi(line);
		x = 0;
		if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y)))
			return (1);
		while (x < data->map_x)
		{
			if(!(data->map[x] = (char*)malloc(sizeof(char) * data->map_x)))
				return(1);
			x++;
		}
	}
	else if (line && line[0] == '0')
	{
		i = 0;
		j = 4;
		while (i < data->map_x)
		{
			data->map[data->m][i] = line[j];
			i++;
			j++;
		}
		ft_putstr_fd("allocated string: \n", 2);
		ft_putstr_fd(data->map[data->m], 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("data->m: \n", 2);
		ft_putnbr_fd(data->m, 2);
		data->m++;
		if (data->m == data->map_y)
		{
			if (construct_map(data) == 1)
				return (1);
			data->m = 0;
			free_map(data);
		}
	}
	else if (line && ft_strstr(line, "Piece"))
	{
		x = 0;
		data->piece_y = ft_atoi(line);
		while (line && *line != ' ')
			line++;
		line++;
		data->piece_x = ft_atoi(line);
		if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y)))
			return (1);
		while (x < data->piece_x)
		{
			if(!(data->piece[x] = (char*)malloc(sizeof(char) * data->piece_x)))
				return(1);
			x++;
		}
	}
	else if (line && (line[0] == '.' || line[0] == '*'))
	{
		i = 0;
		while (i < data->piece_x)
		{
			data->piece[data->p][i] = line[i];
			i++;
		}
		ft_putstr_fd("allocated string: \n", 2);
		ft_putstr_fd(data->piece[data->p], 2);
		ft_putchar_fd('\n', 2);
		data->p++;
		if (data->p == data->piece_y)
		{
			prep_piece(data);
			place_piece(data);
			ft_putnbr(data->coord_y - data->y_offset);
			ft_putchar(' ');
			ft_putnbr(data->coord_x - data->x_offset);
			ft_putchar('\n');
			free_piece(data);
			free_heatmap(data);
			data->p = 0;
		}
	}
	//teststruct(data);
	return (0);
}