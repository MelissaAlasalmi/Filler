#include "filler.h"

void free_data(t_filler *data)
{
	free(data->piece);
	data->y_offset = 0;
  	data->x_offset = 0;
	data->sum = 0;
}

static int get_piece(t_filler *data, char *pieceline, int fd)
{
	int		y;
	char	*line;
	char 	**res;

	y = 0;
	if (!(res = ft_strsplit(&pieceline[5], ' ')))
		return (0);
	data->piece_y = ft_atoi(res[0]);
	data->piece_x = ft_atoi(res[1]);
	if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y)))
		return (0);
	while (y < data->piece_y && get_next_line(fd, &line) == 1)
	{
		if (line)
		{
			data->piece[y] = ft_strdup(line);
			y++;
		}
		if (y == data->piece_y)
			break ;
	}
	free(res[0]);
	free(res[1]);
	free(res);
	return (1);
}

static int get_map(t_filler *data, char *mapline, int fd)
{
	int		y;
	char	*line;
	char 	**res;

	y = 0;
	if (!(res = ft_strsplit(&mapline[7], ' ')))
		return (0);
	data->map_y = ft_atoi(res[0]);
	data->map_x = ft_atoi(res[1]);
	if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y)))
		return (0);
	get_next_line(fd, &line);
	while (y< data->map_y && get_next_line(fd, &line) == 1)
	{
		if (line)
		{
			if (y == data->map_y)
				break ;
			data->map[y] = ft_strdup(&line[4]);
			y++;
		}
	}
	free(res[0]);
	free(res[1]);
	free(res);
	return (1);
}

int		main(int argc, char **argv) // only for debugging with a file
//int main(void)
{
	t_filler *data;
	char *line;
	int fd;
	int fd2; // only for debugging using a file
	argc = 0; // only for debugging + unsused argc
	fd2 = open(argv[1], O_RDONLY); //only for debugging + unused argv
	line = NULL;
	fd = 0;
	if (!(data = (t_filler *)malloc(sizeof(t_filler))))
		return (0);
	while (get_next_line(fd2, &line) == 1)
	{
		if (line && ft_strstr(line, "$$$"))
			data->playernum = ft_atoi(&line[10]);
		if (line && ft_strstr(line, "Plateau"))
			get_map(data, line, fd2);
		if (line && ft_strstr(line, "Piece"))
		{
			if (get_piece(data, line, fd2) == 1)
			{
				construct_map(data);
				teststruct(1, data);
				//free_data(data);
				ft_putnbr(data->coord_y - data->y_offset);
				ft_putchar(' ');
				ft_putnbr(data->coord_x - data->x_offset);
				ft_putchar('\n');
			}
		}
		free(line);
	}
	//free(data);
	return(teststruct(0, data));
}