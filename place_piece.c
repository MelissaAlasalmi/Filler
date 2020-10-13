/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/13 21:58:27 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	save_coords(t_filler *data, int y, int x)
{
	int temp_sum;
	int y_temp;
	int x_temp;
	int x_reset;
	int y_reset;

	temp_sum = 0;
	y_temp = y + data->npiece_y;
	x_temp = x + data->npiece_x;
	x_reset = x;
	y_reset = y;
	while (y == 0 || y < y_temp)
	{
		x = x_reset;
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
		data->coord_y = y_reset;
		data->coord_x = x_reset;
	}
}

static int	check_valid(t_filler *data, int y, int x, int j, int i)
{
	int y_temp;
	int x_temp;
	int x_reset;
	int i_reset;
	int trap;

	y_temp = y + data->npiece_y;
	x_temp = x + data->npiece_x;
	x_reset = x;
	i_reset = i;
	trap = 0;
	while (y < y_temp)
	{
		x = x_reset;
		i = i_reset;
		while (x < x_temp)
		{
			if (data->heatmap[y][x] == -2)
				return (1);
			if (data->heatmap[y][x] == -1)
			{
				if (data->piece[j][i] == '.')
				{
					// ft_putstr_fd("piece char: ", 2);
					// ft_putchar_fd(data->piece[j][i], 2);
					// ft_putchar_fd('\n', 2);
					// ft_putstr_fd("heatmap #: ", 2);
					// ft_putnbr_fd(data->heatmap[y][x], 2);
					// ft_putchar_fd('\n', 2);
					// ft_putstr_fd("swing and miss!", 2);
					// ft_putchar_fd('\n', 2);
				}
				else
					trap++;
			}
			i++;
			x++;
		}
		y++;
		j++;
	}
	if (trap == 0 || trap > 1)
		return (1);
	return (0);
}

void		place_piece(t_filler *data)
{
	int y;
	int x;
	int j;
	int i;

	y = 0;
	while (y <= (data->map_y - data->npiece_y))
	{
		x = 0;
		while (x <= (data->map_x - data->npiece_x))
		{
			j = y;
			while (j < (y + data->npiece_y))
			{
				i = x;
				while (i < (x + data->npiece_x))
				{
					if (data->heatmap[j][i] == -1)
					{
						if (check_valid(data, y, x, data->y_offset, data->x_offset) == 0)
							save_coords(data, y, x);
					}
					i++;
				}
				j++;
			}
			x++;
		}
		y++;
	}
}
