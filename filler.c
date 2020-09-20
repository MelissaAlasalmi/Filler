#include "filler.h"
#include <stdio.h>

static int get_piece(t_piece *piece, char *pieceline, int fd)
{
	int		nb;
	char	*line;
	char 	**res;

	nb = 0;
	if (!(res = ft_strsplit(&pieceline[5], ' ')))
		return (0);
	piece->y = ft_atoi(res[0]);
	piece->x = ft_atoi(res[1]);
	// printf("y: %d\n", piece->y);
	// printf("x: %d\n", piece->x);
	free(res[0]);
	free(res[1]);
	free(res);
	if (!(piece->piece = (char**)malloc(sizeof(char*) * piece->y + 1)))
		return (0);
	ft_putstr_fd("piece y:", 2);
	ft_putnbr_fd(piece->y, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("piece x:", 2);
	ft_putnbr_fd(piece->x, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(line, 2);
	ft_putnbr_fd(fd, 2);
	/*
	while (get_next_line(fd, &line) == 1)
	{
		ft_putstr_fd("IN GNL AT GETPIECE\n", 2);
		if (line)
		{
			piece->piece[nb] = ft_strdup(line);
			nb++;
			ft_putstr_fd("IN LINE AT GETPIECE\n", 2);
		}
	//	ft_strdel(&line);
		if (nb == piece->y)
			break ;
	}
	piece->piece[nb] = NULL;
	*/
	// while (*piece->piece != NULL)
	// {
	// 	printf("piece: %s\n", *piece->piece);
	// 	piece->piece++;
	// }
	return (1);
}

static char	*get_map(t_map *map, char *mapline, int fd)
{
	int		nb;
	int 	y;
	char	*line;
	char 	**res;

	nb = 0;
	y = 0;
	if (!(res = ft_strsplit(&mapline[7], ' ')))
		return (0);
	map->y = ft_atoi(res[0]);
	map->x = ft_atoi(res[1]);
	// printf("y: %d\n", map->y);
	// printf("x: %d\n", map->x);
	free(res[0]);
	free(res[1]);
	free(res);
	if (!(map->map = (char**)malloc(sizeof(char*) * map->x + 1)))
		return (0);
	get_next_line(fd, &line);
	// ft_strdel(&line);
	while (ft_strstr(line, "Piece") == NULL && get_next_line(fd, &line) == 1)
	{
		ft_putstr_fd("IN GNL AT GETMAP\n", 2);
		if (line)
		{	
			if (nb == map->y)
				break ;
			ft_putstr_fd("IN LINE AT GETMAP\n", 2);
			map->map[nb] = ft_strdup(&line[4]);
			if (ft_strstr(line, "O"))
			{
				map->p1_y = ft_atoi(line);
				while (line[y] != 'O')
					y++;
				map->p1_x = y - 4;
				y = 0;
				
			}
			if (ft_strstr(line, "X"))
			{
				map->p2_y = ft_atoi(line);
				while (line[y] != 'X')
					y++;
				map->p2_x = y - 4;
				y = 0;	
			}
			nb++;	
		}
		//ft_strdel(&line);
	}
	map->map[nb] = NULL;
	// while (*map->map != NULL)
	// {
	// 	printf("map: %s\n", *map->map);
	// 	map->map++;
	// }
	// printf("p1_y: %d\n", map->p1_y);
	// printf("p1_x: %d\n", map->p1_x);
	// printf("p2_y: %d\n", map->p2_y);
	// printf("p2_x: %d\n", map->p2_x);
	return (line);
}

static int get_player(t_players *players , char *line)
{
	if (!line || (line[10] != '1' && line[10] != '2'))
		return (0);
	if (line[10] - '0' == 1)
		players->playernum = 1;
	else
		players->playernum = 2;	
	// printf("playernum: %d\n", players->playernum);
	return(1);
}

int		main(int argc, char **argv) // only for debugging with a file
{
	t_map *map;
	t_piece	*piece;
	t_players *players;
	//t_coordinates *coordinates;
	char *line;
	int fd;
	int fd2; // only for debugging using a file
	line = NULL;
	argc = 0; // only for debugging + unsused argc
	fd2 = open(argv[1], O_RDONLY); //only for debugging + unused argv
	fd = 0;
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
		ft_putstr_fd("line before statements:", 2);
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		if (line && ft_strstr(line, "$$$"))
			get_player(players, line);
		if (line && ft_strstr(line, "Plateau"))
			line = get_map(map, line, fd);
		if (line && ft_strstr(line, "Piece"))
		{
			if (get_piece(piece, line, fd) == 1)
				break ;
		}
		ft_putstr_fd("line after statements:", 2);
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putnbr(map->p1_y);
	ft_putchar(' ');
	ft_putnbr(map->p1_x);
	ft_putchar('\n');
	ft_putnbr_fd(map->p1_y, 2);
	ft_putnbr_fd(map->p1_x, 2);
	//coordinates = heatmap(map, piece, players);
	free(map);
	free(piece);
	free(players);
	//close(fd); // only for debugging via file
	return(0);
}