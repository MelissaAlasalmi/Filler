/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/16 10:25:46 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void free_map(t_filler *data)
{
	int i;

	i = 0;
	while (i < data->map_y)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void free_piece(t_filler *data)
{
	int i;

	i = 0;
	while (i < data->piece_y)
	{
		free(data->piece[i]);
		i++;
	}
	free(data->piece);
}

void free_heatmap(t_filler *data)
{
	int i;

	i = 0;
	while (i < data->map_y)
	{
		free(data->heatmap[i]);
		i++;
	}
	free(data->heatmap);
}