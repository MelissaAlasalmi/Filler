#include "filler.h"
#include <stdio.h>

static int	sizes(char *str, int *x, int *y)
{
	char **res;

	if (!(res = ft_strsplit(str, ' ')))
		return (1);
	*y = ft_atoi(res[0]);
	*x = ft_atoi(res[1]);
	// printf("y: %d\n", *y);
	// printf("x: %d\n", *x);
	free(res[0]);
	free(res[1]);
	free(res);
	return (0);
}

static int		get_piece(t_piece *piece, char *pieceline, int fd)
{
	int		nb;
	char	*line;

	nb = 0;
	if (sizes(&pieceline[5], &piece->x, &piece->y))
		return (1);
	if (!(piece->piece = (char**)malloc(sizeof(char*) * piece->y + 1)))
		return (1);
	while (get_next_line(fd, &line))
	{
		if (line)
		{
			piece->piece[nb] = ft_strdup(line);
			nb++;
		}
		ft_strdel(&line);
		if (nb == piece->y)
			break ;
	}
	piece->piece[nb] = NULL;
	// while (*piece->piece != NULL)
	// {
	// 	printf("piece: %s\n", *piece->piece);
	// 	piece->piece++;
	// }
	return (0);
}

static int	get_map(t_map *map, char *mapline, int fd)
{
	int		nb;
	int 	y;
	char	*line;

	nb = 0;
	y = 0;
	if (sizes(&mapline[7], &map->x, &map->y))
		return (1);
	if (!(map->map = (char**)malloc(sizeof(char*) * map->y + 1)))
		return (1);
	get_next_line(fd, &line);
	ft_strdel(&line);
	while (get_next_line(fd, &line))
	{
		if (line)
		{
			map->map[nb] = ft_strdup(&line[4]);
			if (ft_strstr(line, "X"))
			{
				map->p2_x = ft_atoi(line);
				while (line[y] != 'X')
					y++;
				map->p2_y = y - 4;
			}
			y = 0;
			if (ft_strstr(line, "O"))
			{
				map->p1_x = ft_atoi(line);
				while (line[y] != 'O')
					y++;
				map->p1_y = y - 4;
			}
			nb++;
		}
		ft_strdel(&line);
		if (nb == map->y)
			break ;
	}
	map->map[nb] = NULL;
	// while (*map->map != NULL)
	// {
	// 	printf("map: %s\n", *map->map);
	// 	map->map++;
	// }
	// printf("p2_x: %d\n", map->p2_x);
	// printf("p2_y: %d\n", map->p2_y);
	// printf("p1_x: %d\n", map->p1_x);
	// printf("p1_y: %d\n", map->p1_y);
	
	return (0);
}

static int		get_player(t_players *players , char *line)
{
	if (!line || (line[10] != '1' && line[10] != '2'))
		return (1);
	if (line[10] - '0' == 1)
		players->playernum = 1;
	else
		players->playernum = 2;	
	//printf("playernum: %d\n", players->playernum);
	ft_strdel(&line);
	return(0);
}

int			main(int argc, char **argv)
{
	t_map *map;
	t_piece	*piece;
	t_players *players;
//	t_coordinates *coordinates;
	char *line;
	int fd;
	line = NULL;
	argc = 0;
	fd = open(argv[1], O_RDONLY);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (!(piece = (t_piece *)malloc(sizeof(t_piece))))
		return (0);
	if (!(players = (t_players *)malloc(sizeof(t_players))))
		return (0);
	//if (!(coordinates = (t_coordinates *)malloc(sizeof(t_coordinates))))
	//	return (0);
	while (get_next_line(fd, &line) == 1)
	{
		if (line && ft_strstr(line, "$$$"))
		{
			if (get_player(players, line) == 1)
				return (0);
		}
		else if (line && ft_strstr(line, "Plateau"))
		{
			if (get_map(map, line, fd) == 1)
				return (0);
		}
		else if (line && ft_strstr(line, "Piece"))
		{
			if (get_piece(piece, line, fd) == 1)
				return (0);
		}
		else
			ft_strdel(&line);
	}
	//coordinates = heatmap(map, piece, players);
	free(map);
	free(piece);
	free(players);
	close(fd);
	return(0);
	//return (coordinates);
}