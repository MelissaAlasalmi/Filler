/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/12/27 13:03:58 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/* 
* Compares the sum of the values of a newly found viable "sub-map" area to the sum 
* of a previously stored viable "sub-map" area. If the sum of the new viable area
* is smaller than the old one, it is considered a more optimal area to place the 
* piece, so the coordinate variables to be returned to the filler VM are overwritten 
* with the top-left coordinate combo of the new, more optimal area. Otherwise, the
* coordinate variables remain the same.
*/
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

/* 
* Checks the integrity of an area that the program is considering for placing a piece.
* If a part of the piece (a coordinate-combo that has the value of '*') intersects with
* opponent-owned territory (a coordinate-combo that has the value of '-2') this is an 
* illegal move, so hit_or_miss returns 2. Also, if a part of the piece intersects with 
* more than just one coordinate-combo with a value of '-1', this means the piece would 
* overlap too much of the programs' owned territory, also an illegal move. hit_or_miss
* returns the number of coordinate-combos where a part of the piece ('*') intersects with
* program-owned territory ('-1').
*/
static int	hit_or_miss(t_filler *data, int y, int j, int hits)
{
	int x;
	int i;

	while (y < data->y_range)
	{
		x = data->temp_x;
		i = data->x_offset;
		while (x < data->x_range)
		{
			if (data->heatmap[y][x] == -2 && data->piece[j][i] == '*')
				return (2);
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

/* 
* Checks if the playable "sub-map" area (the area surrounding the coordinate-combo 
* given from place_piece that also can successfully fit the piece) includes at least 
* one coordinate-combo with a value of '-1'. A '-1' value in the "sub-map" area means
* this area could possibly be a viable place to place the piece, which can be
* identified in the hit_or_miss function - if hit_or_miss returns 1, this area is viable.
*/
void		check_coords(t_filler *data, int y)
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

/* 
* Scans through the playable map area (piece offset removed), one coordinate-combo 
* at a time, sending the coordinate-combo to check_coords to be examined further.
*/
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
			check_coords(data, data->temp_y);
			x++;
		}
		y++;
	}
}

/* 
* For a set amount of turns, this function uses a different strategy than 
* its sister, place_piece, when the program is assigned p2 - it forces piece 
* placement into a defensive position to avoid being surrounded by the opponent.
*/
void		place_piece_p2(t_filler *data, int ylimit, int xreset)
{
	int y;
	int x;

	y = 0;
	while (y <= (ylimit - data->npiece_y))
	{
		x = xreset;
		data->temp_y = y;
		while (x <= (data->map_x - data->npiece_x))
		{
			data->temp_x = x;
			check_coords(data, data->temp_y);
			if (data->coord_y == 0 && data->coord_x == 0)
				place_piece(data);
			x++;
		}
		y++;
	}
	data->index++;
}
