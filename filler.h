/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:33:23 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/20 08:46:46 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"
# include <fcntl.h>


typedef struct	s_filler
{

	int		player;
	char	**map;
	int		**heatmap;
	int		map_y;
	int		map_x;
	int		m;
	char	**piece;
	int		piece_y;
	int		piece_x;
	int		p;
	int		tempheatmap;
	int		y_offset;
	int		x_offset;
	int		npiece_y;
	int		npiece_x;
	int		temp_y;
	int		temp_x;
	int		y_range;
	int		x_range;
	int		coord_y;
	int		coord_x;
	int		sum;
	int		extra;
}				t_filler;

t_filler		*initialize_struct(void);
void			re_initialize(t_filler *data);
int				get_data(t_filler *data, char *line);
int				construct_map(t_filler *map);
void			prep_piece(t_filler *map);
void			place_piece_p2(t_filler *data, int ylimit, int xreset);
void			place_piece(t_filler *data);
void			check_coords(t_filler *data, int y);
void			free_map(t_filler *data);
void			free_piece(t_filler *data);
void			free_heatmap(t_filler *data);

#endif
