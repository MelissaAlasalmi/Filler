#include "filler.h"

void testheatmap(t_filler *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    ft_putstr_fd("new heatmap:\n", 2);
    if (data->heatmap)
    {
        while (i < data->map_y)
        {
            while (j < data->map_x)
            {
                if (data->heatmap[i][j] < 10)
                {
                    ft_putchar_fd(' ', 2);
                    if (data->heatmap[i][j] > 0)
                        ft_putchar_fd(' ', 2);
                }
                else
                    ft_putchar_fd(' ', 2);
                ft_putnbr_fd(data->heatmap[i][j], 2);
                ft_putchar_fd('|', 2);
                j++;
            }
            ft_putchar_fd('\n', 2);
            i++;
            j = 0;
        }
    }
}

void testmap(t_filler *data)
{
    int i;
    i = 0;
    ft_putstr_fd("map:\n", 2);
    while (i < data->map_y)
    {
        ft_putstr_fd(data->map[i], 2);
        ft_putchar_fd('\n', 2);
        i++;
    }
}

void testpiece(t_filler *data)
{
    int i;

    i = 0;
    ft_putstr_fd("piece:\n", 2);
    if (data->piece)
    {
        while (i < data->piece_y)
        {
            ft_putstr_fd(data->piece[i], 2);
            ft_putchar_fd('\n', 2);
            i++;

        }
    }
}
