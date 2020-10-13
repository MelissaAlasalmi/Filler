/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/13 20:51:53 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*initialize_struct(void)
{
	t_filler *data;

	if (!(data = (t_filler *)malloc(sizeof(t_filler))))
		return (NULL);
	data->map_y = 0;
	data->map_x = 0;
	data->m = 0;
	data->piece_y = 0;
	data->piece_x = 0;
	data->p = 0;
	data->y_offset = 0;
	data->x_offset = 0;
	data->npiece_y = 0;
	data->npiece_x = 0;
	data->coord_y = 0;
	data->coord_x = 0;
	data->sum = 0;
	data->extra = 0;
	return (data);
}

int			main(void)
{
	t_filler	*data;
	char		*line;
	int			i;
	int			p;

	data = initialize_struct();
	line = NULL;
	p = 0;
	while (get_next_line(0, &line) == 1)
	{
		i = 0;
		if (line && ft_strstr(line, "$$$"))
			p = ft_atoi(&line[10]);
		i = get_data(data, line, p);
		if (i == 1)
		{
			free(data);
			return (1);
		}
		if (i == 2)
			data = initialize_struct();
		ft_strdel(&line);
	}
	return (0);
}
