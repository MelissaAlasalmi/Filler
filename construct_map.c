/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/19 20:12:02 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		place_piece_p2(t_filler *data, int ylimit, int xreset)
{
	int y;
	int x;
	
	y = 0;
	while (y <= ylimit)
	{
		x = xreset;
		data->temp_y = y;
		while (x <= (data->map_x - data->npiece_x))
		{
			data->temp_x = x;
			check_coords(data, data->temp_y);
			x++;
		}
		y++;
	}
	data->tempheatmap++;
}

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
	if (data->player == 2)
	{
		while(data->tempheatmap < 70)
			place_piece_p2(data, 20, 26);
	}
	return (0);
}
