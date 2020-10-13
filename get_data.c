/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/13 21:10:25 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	find_optimal_coords(t_filler *data)
{
	prep_piece(data);
	place_piece(data);
	ft_putnbr(data->coord_y - data->y_offset);
	ft_putchar(' ');
	ft_putnbr(data->coord_x - data->x_offset);
	ft_putchar('\n');
	free(data);
	return (2);
}

static int	get_piece_coords(t_filler *data, char *line)
{
	char	**coord;
	int		y;

	coord = NULL;
	y = 0;
	if (!(coord = ft_strsplit(&line[5], ' ')))
		return (1);
	data->piece_y = ft_atoi(coord[0]);
	data->piece_x = ft_atoi(coord[1]);
	if (!(data->piece = (char**)malloc(sizeof(char*) * data->piece_y)))
		return (1);
	while (y < data->piece_y)
	{
		if (!(data->piece[y] = (char*)malloc(sizeof(char) * data->piece_x)))
			return (1);
		y++;
	}
	free(coord);
	return (0);
}

static int	get_map(t_filler *data, char *line, int p)
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
	return (0);
}

static int	get_map_coords(t_filler *data, char *line)
{
	char	**coord;
	int		y;

	coord = NULL;
	y = 0;
	if (!(coord = ft_strsplit(&line[7], ' ')))
		return (1);
	data->map_y = ft_atoi(coord[0]);
	data->map_x = ft_atoi(coord[1]);
	if (!(data->map = (char**)malloc(sizeof(char*) * data->map_y)))
		return (1);
	while (y < data->map_y)
	{
		if (!(data->map[y] = (char*)malloc(sizeof(char) * data->map_x)))
			return (1);
		y++;
	}
	free(coord);
	return (0);
}

int			get_data(t_filler *data, char *line, int p)
{
	int i;

	i = 0;
	if (line && ft_strstr(line, "Plateau"))
		i = get_map_coords(data, line);
	else if (line[0] == '0')
		i = get_map(data, line, p);
	else if (ft_strstr(line, "Piece"))
		i = get_piece_coords(data, line);
	else if (line && (line[0] == '.' || line[0] == '*'))
	{
		data->piece[data->p] = ft_strdup(line);
		data->p++;
	}
	if (data->p != 0 && data->p == data->piece_y)
		i = find_optimal_coords(data);
	return (i);
}
