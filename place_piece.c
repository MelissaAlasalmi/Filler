/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/15 11:56:41 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	save_coords(t_filler *data)
{
	int temp_sum;
	int y;
	int x;
	int y_temp;
	int x_temp;

	y = data->temp_y;
	y_temp = data->temp_y + data->npiece_y;
	x_temp = data->temp_x + data->npiece_x;
	temp_sum = 0;
	while (y == 0 || y < y_temp)
	{
		x = data->temp_x;
		while (x == 0 || x < x_temp)
		{
			ft_putstr_fd("check coord for sum: ", 2);
            ft_putnbr_fd(y, 2);
            ft_putchar_fd(' ', 2);
            ft_putnbr_fd(x, 2);
            ft_putchar_fd('\n', 2);
			ft_putstr_fd("value at coords: ", 2);
            ft_putnbr_fd(data->heatmap[y][x], 2);
            ft_putchar_fd('\n', 2);
			temp_sum = temp_sum + data->heatmap[y][x];
			ft_putstr_fd("sum: ", 2);
            ft_putnbr_fd(temp_sum, 2);
            ft_putchar_fd('\n', 2);
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
    testpiece(data);
	while (y < y_range)
	{
		x = data->temp_x;
		i = data->x_offset;
		while (x < x_range)
		{
			ft_putstr_fd("check coord for hits: ", 2);
            ft_putnbr_fd(y, 2);
            ft_putchar_fd(' ', 2);
            ft_putnbr_fd(x, 2);
            ft_putchar_fd('\n', 2);
			if (data->heatmap[y][x] == -2)
				return (1);
			if (data->heatmap[y][x] == -1)
			{
				ft_putstr_fd("piece char: ", 2);
				ft_putchar_fd(data->piece[j][i], 2);
				ft_putchar_fd('\n', 2);
				ft_putstr_fd("heatmap #: ", 2);
				ft_putnbr_fd(data->heatmap[y][x], 2);
				ft_putchar_fd('\n', 2);
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
	ft_putstr_fd("coord_y: ", 2);
    ft_putnbr_fd(data->temp_y, 2);
    ft_putchar_fd('\n', 2);
    ft_putstr_fd("coord_x: ", 2);
    ft_putnbr_fd(data->temp_x, 2);
    ft_putchar_fd('\n', 2);
	
	ft_putstr_fd("y_range: ", 2);
    ft_putnbr_fd(y_range, 2);
    ft_putchar_fd('\n', 2);
    ft_putstr_fd("x_range: ", 2);
    ft_putnbr_fd(x_range, 2);
    ft_putchar_fd('\n', 2);

	result = hit_or_miss(data, y_range, x_range);
	ft_putstr_fd("result: ", 2);
    ft_putnbr_fd(result, 2);
    ft_putchar_fd('\n', 2);
	if (result == 0 || result > 1)
		return (1);
	return (0);
}

static void	check_coords(t_filler *data)
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
					save_coords(data);
			}
			x++;
		}
		y++;
	}
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
			check_coords(data);
			x++;
		}
		y++;
	}
}
