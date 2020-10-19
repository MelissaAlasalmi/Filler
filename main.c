/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/19 20:04:32 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			re_initialize(t_filler *data)
{
	data->map_y = 0;
	data->map_x = 0;
	data->m = 0;
	data->tempheatmap = 0;
	data->piece_y = 0;
	data->piece_x = 0;
	data->p = 0;
	data->y_offset = 0;
	data->x_offset = 0;
	data->npiece_y = 0;
	data->npiece_x = 0;
	data->temp_y = 0;
	data->temp_x = 0;
	data->y_range = 0;
	data->x_range = 0;
	data->coord_y = 0;
	data->coord_x = 0;
	data->sum = 0;
	data->extra = 0;
}

t_filler		*initialize_struct(void)
{
	t_filler *data;

	if (!(data = (t_filler *)malloc(sizeof(t_filler))))
		return (NULL);
	data->map = NULL;
	data->heatmap = NULL;
	data->piece = NULL;
	re_initialize(data);
	return (data);
}

int				main(void)
{
	t_filler	*data;
	char		*line;
	int			i;

	line = NULL;
	i = 0;
	data = initialize_struct();
	while (get_next_line(0, &line) > 0)
	{
		if (line && ft_strstr(line, "$$$"))
			data->player = ft_atoi(&line[10]);
		i = get_data(data, line);
		if (i == 1)
		{
			free(data);
			return (1);
		}
		if (i == 2)
			re_initialize(data);
		ft_strdel(&line);
	}
	free(data);
	return (0);
}
