/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/12/27 12:24:41 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/* 
* "Prepares" the piece for placement by handling the offsets of the piece, if any,
* then calls the place_piece function to find the optimal coordinates to place the
* piece on the map
*/
static int	find_optimal_coords(t_filler *data)
{
	prep_piece(data);
	if (data->player == 2)
	{
		if (data->map_x < 18)
			place_piece_p2(data, 13, 10);
		else if (data->map_x > 18 && data->map_x < 41 && data->index < 120)
			place_piece_p2(data, 20, 15);
		else
			place_piece(data);
	}
	else
		place_piece(data);
	ft_putnbr(data->coord_y - data->y_offset);
	ft_putchar(' ');
	ft_putnbr(data->coord_x - data->x_offset);
	ft_putchar('\n');
	free_piece(data);
	free_heatmap(data);
	return (2);
}

/* 
* Analyses the data received from get_data and stores it into the piece 
* coordinate variables of the struct. Also allocates space for the piece
* array.
*/
static int	get_piece_coords(t_filler *data, char *line)
{
	char	**coord;
	int		y;

	coord = NULL;
	y = 0;
	if (!(coord = ft_strsplit(&line[5], ' ')))
		return (1);
	data->piece_y = ft_atoi(coord[0]);
	data->piece_x = ft_atoi(coord[1]);
	if (!(data->piece = (char**)malloc(sizeof(char*) * (data->piece_y + 1))))
		return (1);
	free(coord[0]);
	free(coord[1]);
	free(coord);
	return (0);
}

/* 
* Analyses the data received from get_data and stores it into the map 
* array of the struct. Also calls construct_map to generate a heatmap
* based on the data of the map.
*/
static int	get_map(t_filler *data, char *line)
{
	data->map[data->m] = ft_strdup(&line[4]);
	data->m++;
	if (data->m == data->map_y)
	{
		if (construct_map(data) == 1)
			return (1);
		data->m = 0;
		free_map(data);
	}
	return (0);
}

/* 
* Analyses the data received from get_data and stores it into the map 
* coordinate variables of the struct. 
*/
static int	get_map_coords(t_filler *data, char *line)
{
	char	**coord;
	int		y;

	coord = NULL;
	y = 0;
	if (!(coord = ft_strsplit(&line[7], ' ')))
		return (1);
	data->map_y = ft_atoi(coord[0]);
	data->map_x = ft_atoi(coord[1]);
	if (!(data->map = (char**)malloc(sizeof(char*) * (data->map_y + 1))))
		return (1);
	free(coord[0]);
	free(coord[1]);
	free(coord);
	return (0);
}

/* 
* Analyses the data received from get_next_line and sends it to the appropriate
* function for storage (get_map_coords, get_map, or get_piece_coords) or stores it 
* directly into the piece array if it does not meet the criteria for any of the 
* storage functions. Once the last line of the piece is stored, the 
* find_optimal_coords function fires up the algorithm! 
*/
int			get_data(t_filler *data, char *line)
{
	int i;

	i = 0;
	if (line && ft_strstr(line, "Plateau"))
		i = get_map_coords(data, line);
	else if (line[0] == '0')
		i = get_map(data, line);
	else if (ft_strstr(line, "Piece"))
		i = get_piece_coords(data, line);
	else if (line && (line[0] == '.' || line[0] == '*'))
	{
		data->piece[data->p] = ft_strdup(line);
		data->p++;
	}
	if (data->p != 0 && data->p == data->piece_y)
		i = find_optimal_coords(data);
	return (i);
}
