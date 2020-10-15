/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/15 13:46:40 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	save_coords(t_filler *data, int y, int temp_sum)
{
	int x;

	while (y == 0 || y < data->y_range)
	{
		x = data->temp_x;
		while (x == 0 || x < data->x_range)
		{
			temp_sum = temp_sum + data->heatmap[y][x];
			x++;
		}
		y++;
	}
	if (temp_sum < data->sum || data->sum == 0)
	{
		data->sum = temp_sum;
		data->coord_y = data->temp_y;
		data->coord_x = data->temp_x;
	}
}

static int	hit_or_miss(t_filler *data, int y, int j, int hits)
{
	int x;
	int i;
	int conflicts;
	
	conflicts = 0;
	while (y < data->y_range)
	{
		x = data->temp_x;
		i = data->x_offset;
		while (x < data->x_range)
		{
			if (data->heatmap[y][x] == -2)
			{
				if (data->piece[j][i] == '*')
					conflicts = 2;
			}
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
	return (hits + conflicts);
}

static void	check_coords(t_filler *data, int y) //scans map, within playable piece area, coord by coord, for a possible placement
{
	int x;
	int result;
	
	data->y_range = data->temp_y + data->npiece_y;
	data->x_range = data->temp_x + data->npiece_x;
	while (y < data->y_range)
	{
		x = data->temp_x;
		while (x < data->x_range)
		{
			if (data->heatmap[y][x] == -1)
			{
				result = hit_or_miss(data, data->temp_y, data->y_offset, 0);
				if (result == 1)
					save_coords(data, data->temp_y, 0);
			}
			x++;
		}
		y++;
	}
}

void		place_piece(t_filler *data) //scans map, coord by coord, within playable area
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
			check_coords(data, data->temp_y);
			x++;
		}
		y++;
	}
}
