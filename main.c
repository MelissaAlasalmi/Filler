#include "filler.h"

t_filler *initialize_struct(void)
{
	t_filler *data;

	if (!(data = (t_filler *)malloc(sizeof(t_filler))))
		return (NULL);
	data->playernum = 0;
	//data->map = NULL;
	data->heatmap = NULL;
	data->map_y = 0;
	data->map_x = 0;
	data->m = 0;
	data->piece = NULL;
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
	return (data);
}

int		main(int argc, char **argv)
{
	t_filler *data;
	char *line;
	int fd;

	data = initialize_struct();
	line = NULL;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (scan_fd(data, line) == 1)
		{
			free(data);
			return (1);
		}
		ft_strdel(&line);
	}
	free(data);
	return(0);
}