#include "filler.h"

static int get_piece(t_filler *data, char *pieceline, int fd)
{
	int		y;
	char	*line;
	char 	**res;

	y = 0;
	if (!(res = ft_strsplit(&pieceline[5], ' ')))
		return (1);
	data->piece_y = ft_atoi(res[0]);
	data->piece_x = ft_atoi(res[1]);
	if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y)))
		return (1);
	while (y < data->piece_y && get_next_line(fd, &line) == 1)
	{
		// ft_putstr_fd("line in get_piece: ", 2);
		// ft_putstr_fd(line, 2);
		// ft_putchar_fd('\n', 2);
		if (line)
		{
			data->piece[y] = ft_strdup(line);
			y++;
		}
		if (y == data->piece_y)
			break ;
	}
	//testpiece(data);
	free(res[0]);
	free(res[1]);
	free(res);
	return (0);
}

static int get_map(t_filler *data, char *line, int fd)
{
	int y;

	y = 1;
	if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y)))
			return (1);
	data->map[0] = ft_strdup(&line[4]);
	while (y < data->map_y && get_next_line(fd, &line) == 1)
	{
		if (line)
		{	
			// ft_putstr_fd("line in get_map: ", 2);
			// ft_putstr_fd(line, 2);
			// ft_putchar_fd('\n', 2);
			if (y == data->map_y)
				break ;
			data->map[y] = ft_strdup(&line[4]);
			y++;
		}
	}
	//testmap(data);
	return (0);
}

static int get_mapcoords(t_filler *data, char *line)
{
	char 	**plateau;

	if (!(plateau = ft_strsplit(&line[7], ' ')))
		return (1);
	data->map_y = ft_atoi(plateau[0]);
	data->map_x = ft_atoi(plateau[1]);
	free(plateau[0]);
	free(plateau[1]);
	free(plateau);
	return (0);
}

int scan_fd(t_filler *data, char *line, int fd)
{
	// ft_putstr_fd("line in scan: ", 2);
	// ft_putstr_fd(line, 2);
	// ft_putchar_fd('\n', 2);
	if (line && ft_strstr(line, "$$$"))
			data->playernum = ft_atoi(&line[10]);
	else if (line && ft_strstr(line, "Plateau"))
	{
			if (get_mapcoords(data, line) == 1)
				return (1);
	}
	else if (line && ft_strstr(line, "000"))
	{
			if (get_map(data, line, fd) == 1)
				return (1);
			construct_map(data);
	}
	else if (line && ft_strstr(line, "Piece"))
	{
		if (get_piece(data, line, fd) == 1)
			return (1);
		prep_piece(data);
		place_piece(data);
		ft_putnbr(data->coord_y - data->y_offset);
		ft_putchar(' ');
		ft_putnbr(data->coord_x - data->x_offset);
		ft_putchar('\n');
		free_piece(data);
	}
	//teststruct(data);
	ft_strdel(&line);

	return (0);
}