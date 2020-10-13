#include "filler.h"

t_filler *initialize_struct(void)
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

int		main(int argc, char **argv)
{
	t_filler *data;
	char *line;
	int fd;
	int i;
	int p;

	data = initialize_struct();
	line = NULL;
	i = 0;
	p = 0;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (line && ft_strstr(line, "$$$"))
			p = ft_atoi(&line[10]);
		i = scan_fd(data, line, p);
		if (i == 1)
		{
			free(data);
			return (1);
		}
		if (i == 2)
		{
			free(data);
			data = initialize_struct();
		}
		ft_strdel(&line);
		i = 0;
	}
	return(0);
}