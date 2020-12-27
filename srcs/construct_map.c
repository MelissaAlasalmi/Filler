/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/12/27 12:21:42 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/* 
* For each coordinate in the base of the heatmap that has '0' value, a new int 
* value is assigned to it based on its relative position to the nearest 
* opponent-owned coordinate.
*/
static int		fill_heatmap(t_filler *data, int row, int column)
{
	int y;
	int x;
	int distance;
	int min;

	y = 0;
	min = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->heatmap[y][x] == -2)
			{
				distance = ft_abs(x - column);
				distance += ft_abs(y - row);
				if (distance < min || min == 0)
					min = distance;
			}
			x++;
		}
		y++;
	}
	return (min);
}

static void		construct_heatmap(t_filler *data)
{
	int y;
	int x;

	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->heatmap[y][x] == 0)
				data->heatmap[y][x] = fill_heatmap(data, y, x);
			x++;
		}
		y++;
	}
}

/* 
* Converts the data from the map into the base of the heatmap: '.' becomes
* '0', and letters 'o', 'O', 'x' and 'X' become either '-1' or '-2'. 
* '-1' is always used to represent the programs' pieces on the map, and 
* '-2' is always used to represent the opponents' pieces on the map.
*/
static void		convert_data(t_filler *data, int y, int x)
{
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->map[y][x] == '.')
				data->heatmap[y][x] = 0;
			if (data->map[y][x] == 'o' || data->map[y][x] == 'O')
			{
				if (data->player == 1)
					data->heatmap[y][x] = -1;
				else
					data->heatmap[y][x] = -2;
			}
			if (data->map[y][x] == 'x' || data->map[y][x] == 'X')
			{
				if (data->player == 2)
					data->heatmap[y][x] = -1;
				else
					data->heatmap[y][x] = -2;
			}
			x++;
		}
		y++;
	}
}

int				construct_map(t_filler *data)
{
	int y;

	y = 0;
	if (!(data->heatmap = (int**)malloc(sizeof(int*) * data->map_y)))
		return (1);
	while (y < data->map_y)
	{
		if (!(data->heatmap[y] = (int*)malloc(sizeof(int) * data->map_x)))
			return (1);
		y++;
	}
	convert_data(data, 0, 0);
	construct_heatmap(data);
	return (0);
}
