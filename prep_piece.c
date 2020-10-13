/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/13 21:38:17 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_x_offset(t_filler *data, int y, int x)
{
	int x_offset;
	int temp_offset;

	x_offset = data->piece_x;
	y = y + data->y_offset;
	while (y < data->piece_y)
	{
		x = 0;
		temp_offset = 0;
		while (x < data->piece_x)
		{
			if (data->piece[y][x] == '.')
			{
				while (data->piece[y][x] == '.')
				{
					temp_offset++;
					x++;
				}
			}
			else
				break ;
		}
		if (temp_offset < x_offset)
			x_offset = temp_offset;
		y++;
	}
	data->x_offset = x_offset;
	data->npiece_x = data->piece_x - x_offset;
}

void	get_y_offset(t_filler *data, int y, int x)
{
	int y_offset;

	y_offset = 0;
	while (y < data->piece_y)
	{
		while (data->piece[y][x] == '.')
			x++;
		if (x == data->piece_x)
		{
			y_offset++;
			x = 0;
			y++;
		}
		else
			break ;
	}
	data->y_offset = y_offset;
	data->npiece_y = data->piece_y - data->y_offset;
}

void	prep_piece(t_filler *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	get_y_offset(data, y, x);
	get_x_offset(data, y, x);
	x = data->x_offset;
	while (data->piece[data->y_offset][x] == '.')
	{
		data->extra++;
		x++;
	}
}
