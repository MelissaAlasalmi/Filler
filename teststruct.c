#include "filler.h"

int teststruct(int power, t_filler *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (power == 1)
    {
        ft_putstr_fd("playernum: ", 2);
        ft_putnbr_fd(data->playernum, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("map_y: ", 2);
        ft_putnbr_fd(data->map_y, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("map_x: ", 2);
        ft_putnbr_fd(data->map_x, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("map:\n", 2);
        while (data->map[i] != NULL)
        {
            ft_putstr_fd(data->map[i], 2);
            ft_putchar_fd('\n', 2);
            i++;
        }
        ft_putchar_fd('\n', 2);
        i = 0;
        ft_putstr_fd("p1_y: ", 2);
        ft_putnbr_fd(data->p1_y, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("p1_x: ", 2);
        ft_putnbr_fd(data->p1_x, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("p2_y: ", 2);
        ft_putnbr_fd(data->p2_y, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("p2_x: ", 2);
        ft_putnbr_fd(data->p2_x, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("piece_y: ", 2);
        ft_putnbr_fd(data->piece_y, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("piece_x: ", 2);
        ft_putnbr_fd(data->piece_x, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("piece:\n", 2);
        while (data->piece[i] != NULL)
        {
            ft_putstr_fd(data->piece[i], 2);
            ft_putchar_fd('\n', 2);
            i++;

        }
        ft_putstr_fd("new heatmap:\n", 2);
        i = 0;
        j = 0;
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
        ft_putstr_fd("y_offset: ", 2);
        ft_putnbr_fd(data->row_offset, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd("x_offset: ", 2);
        ft_putnbr_fd(data->column_offset, 2);
        ft_putchar_fd('\n', 2);
        return (0);
    }
    else
        return (0);
}