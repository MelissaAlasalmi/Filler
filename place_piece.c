/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/14 17:35:31 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	save_coords(t_filler *data)
{
	int temp_sum;
	int y;
	int x;
	int y_temp;
	int x_temp;

	y = data->temp_y;
	x = data->temp_x;
	y_temp = data->temp_y + data->npiece_y;
	x_temp = data->temp_x + data->npiece_x;
	while (y == 0 || y < y_temp)
	{
		x = data->temp_x;
		while (x == 0 || x < x_temp)
		{
			temp_sum = temp_sum + data->heatmap[y][x];
			x++;
		}
		y++;
	}
	if (temp_sum < data->sum || data->sum == 0)
	{
		data->sum = temp_sum;
		return (0);
	}
	return (1);
}

static int	hit_or_miss(t_filler *data, int y_range, int x_range)
{
	int y;
	int x;
	int i;
	int j;
	int hits;

	y = data->temp_y;
	j = data->y_offset;
	hits = 0;
	while (y < y_range)
	{
		x = data->temp_x;
		i = data->x_offset;
		while (x < x_range)
		{
			if (data->heatmap[y][x] == -2)
				return (1);
			if (data->heatmap[y][x] == -1)
			{
				if (data->piece[j][i] == '*')
					hits++;
			}
			i++;
			x++;
		}
		y++;
		j++;
	}
	return (hits);
}

static int	check_valid(t_filler *data)
{
	int y_range;
	int x_range;
	int result;

	y_range = data->temp_y + data->npiece_y;
	x_range = data->temp_x + data->npiece_x;
	result = hit_or_miss(data, y_range, x_range);
	if (result == 0 || result > 1)
		return (1);
	return (0);
}

static int	check_coords(t_filler *data)
{
	int y;
	int x;

	y = data->temp_y;
	while (y < (data->temp_y + data->npiece_y))
	{
		x = data->temp_x;
		while (x < (data->temp_x + data->npiece_x))
		{
			if (data->heatmap[y][x] == -1)
			{
				if (check_valid(data) == 0)
				{
					if (save_coords(data) == 0)
						return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

void		place_piece(t_filler *data)
{
	int y;
	int x;

	y = 0;
	while (y <= (data->map_y - data->npiece_y))
	{
		x = 0;
		data->temp_y = y;
		while (x <= (data->map_x - data->npiece_x))
		{
			data->temp_x = x;
			if (check_coords(data) == 0)
			{
				data->coord_y = y;
				data->coord_x = x;
			}
			x++;
		}
		y++;
	}
}
