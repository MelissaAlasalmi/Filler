#include "filler.h"

static int get_piece(t_filler *data, char *pieceline, int fd)
{
	int		row;
	char	*line;
	char 	**res;

	row = 0;
	if (!(res = ft_strsplit(&pieceline[5], ' ')))
		return (0);
	data->piece_y = ft_atoi(res[0]);
	data->piece_x = ft_atoi(res[1]);
	if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y + 1)))
		return (0);
	while (row < data->piece_y && get_next_line(fd, &line) == 1)
	{
		if (line)
		{
			data->piece[row] = ft_strdup(line);
			row++;
		}
		if (row == data->piece_y)
			break ;
	}
	data->piece[row] = NULL;
	free(res[0]);
	free(res[1]);
	free(res);
	return (1);
}

static char	*get_map(t_filler *data, char *mapline, int fd)
{
	int		row;
	int 	y;
	char	*line;
	char 	**res;

	row = 0;
	y = 0;
	if (!(res = ft_strsplit(&mapline[7], ' ')))
		return (0);
	data->map_y = ft_atoi(res[0]);
	data->map_x = ft_atoi(res[1]);
	if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y + 1)))
		return (0);
	get_next_line(fd, &line);
	while (ft_strstr(line, "Piece") == NULL && get_next_line(fd, &line) == 1)
	{
		if (line)
		{	
			if (row == data->map_y)
				break ;
			data->map[row] = ft_strdup(&line[4]);
			if (ft_strstr(line, "O"))
			{
				data->p1_y = ft_atoi(line);
				while (line[y] != 'O')
					y++;
				data->p1_x = y - 4;
				y = 0;
			}
			if (ft_strstr(line, "X"))
			{
				data->p2_y = ft_atoi(line);
				while (line[y] != 'X')
					y++;
				data->p2_x = y - 4;
				y = 0;	
			}
		row++;
		}
	}
	data->map[row] = NULL;
	free(res[0]);
	free(res[1]);
	free(res);
	return (line);
}

int		main(int argc, char **argv) // only for debugging with a file
{
	t_filler *data;
	char *line;
	int fd;
	int fd2; // only for debugging using a file
	line = NULL;
	argc = 0; // only for debugging + unsused argc
	fd2 = open(argv[1], O_RDONLY); //only for debugging + unused argv
	fd = 0;
	if (!(data = (t_filler *)malloc(sizeof(t_filler))))
		return (0);
	while (get_next_line(fd2, &line) == 1)
	{
		if (line && ft_strstr(line, "$$$"))
			data->playernum = ft_atoi(&line[10]);
		if (line && ft_strstr(line, "Plateau"))
			line = get_map(data, line, fd2);
		if (line && ft_strstr(line, "Piece"))
		{
			if (get_piece(data, line, fd2) == 1)
			{
				construct_map(data);
				break ;
			}
		}
	}
	//free(data);
	return(teststruct(1, data));
}