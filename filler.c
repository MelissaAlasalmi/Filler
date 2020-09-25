#include "filler.h"

static int get_piece(t_filler *data, char *pieceline, int fd)
{
	int		nb;
	char	*line;
	char 	**res;

	nb = 0;
	if (!(res = ft_strsplit(&pieceline[5], ' ')))
		return (0);
	data->piece_y = ft_atoi(res[0]);
	data->piece_x = ft_atoi(res[1]);
	free(res[0]);
	free(res[1]);
	free(res);
	if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y + 1)))
		return (0);
	while (nb < data->piece_y && get_next_line(fd, &line) == 1)
	{
		if (line)
		{
			data->piece[nb] = ft_strdup(line);
			nb++;
		}
		if (nb == data->piece_y)
			break ;
	}
	data->piece[nb] = NULL;
	return (1);
}

static char	*get_map(t_filler *data, char *mapline, int fd)
{
	int		nb;
	int 	y;
	char	*line;
	char 	**res;

	nb = 0;
	y = 0;
	if (!(res = ft_strsplit(&mapline[7], ' ')))
		return (0);
	data->map_y = ft_atoi(res[0]);
	data->map_x = ft_atoi(res[1]);
	free(res[0]);
	free(res[1]);
	free(res);
	if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y + 1)))
		return (0);
	get_next_line(fd, &line);
	while (ft_strstr(line, "Piece") == NULL && get_next_line(fd, &line) == 1)
	{
		if (line)
		{	
			if (nb == data->map_y)
				break ;
			data->map[nb] = ft_strdup(&line[4]);
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
			nb++;
		}
	}
	data->map[nb] = NULL;
	return (line);
}

static int get_player(t_filler *data , char *line)
{
	if (!line || (line[10] != '1' && line[10] != '2'))
		return (0);
	if (line[10] - '0' == 1)
		data->playernum = 1;
	else
		data->playernum = 2;	
	printf("playernum: %d\n", data->playernum);
	return(1);
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
	while (get_next_line(fd2, &line) == 1)
	{
		if (!(data = (t_filler *)malloc(sizeof(t_filler))))
			return (0);
		if (line && ft_strstr(line, "$$$"))
		{
			if (get_player(data, line) == 0)
				break ;
		}
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
		free(data);
	}
	return(teststruct(1, data));
}