#include "filler.h"

int		main(int argc, char **argv)
{
	t_filler *data;
	char *line;
	int fd;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	line = NULL;
	if (!(data = (t_filler *)malloc(sizeof(t_filler))))
		return (1);
	while (get_next_line(fd, &line) == 1) //change 'fd2' to '0' for VM
	{
		if (scan_fd(data, line, fd) == 1) //change 'fd2' to '0' for VM
		{
			free(data);
			ft_putstr_fd("Main loop returning 1.\n", 2);
			return (1);
		}
	}
	free(data);
	return(0);
}