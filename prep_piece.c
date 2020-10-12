#include "filler.h"

void get_x_offset(t_filler *data, int y, int x)
{
    int x_offset;
    int temp_offset;

    x_offset = data->piece_x;
    y = y + data->y_offset;
    // ft_putstr_fd("x_offset: ", 2);
    // ft_putnbr_fd(data->x_offset, 2);
    // ft_putchar_fd('\n', 2);
    // ft_putstr_fd("npiece_x: ", 2);
    // ft_putnbr_fd(data->npiece_x, 2);
    // ft_putchar_fd('\n', 2);
    while (y < data->piece_y)
    {
        x = 0;
        temp_offset = 0;
        while (x < data->piece_x)
        {
            if (data->piece[y][x] == '.')
            {
                while (data->piece[y][x] == '.')
                {
                    temp_offset++;
                    x++;
                }
            }
            else
                break ;
        }
        if (temp_offset < x_offset)
            x_offset = temp_offset;
        y++;
    }
    data->x_offset = x_offset;
    data->npiece_x = data->piece_x - x_offset;
    // ft_putstr_fd("x_offset: ", 2);
    // ft_putnbr_fd(data->x_offset, 2);
    // ft_putchar_fd('\n', 2);
    // ft_putstr_fd("npiece_x: ", 2);
    // ft_putnbr_fd(data->npiece_x, 2);
    // ft_putchar_fd('\n', 2);
}

void get_y_offset(t_filler *data, int y, int x)
{
    int y_offset;

    y_offset = 0;
    // ft_putstr_fd("y_offset: ", 2);
    // ft_putnbr_fd(data->y_offset, 2);
    // ft_putchar_fd('\n', 2);
    // ft_putstr_fd("npiece_y: ", 2);
    // ft_putnbr_fd(data->npiece_y, 2);
    // ft_putchar_fd('\n', 2);
    while (y < data->piece_y)
	{
        while (data->piece[y][x] == '.')
            x++;
        if (x == data->piece_x)
        {
            y_offset++;
            x = 0;
            y++;
        }
        else
            break ;
    }
    data->y_offset = y_offset;
    data->npiece_y = data->piece_y - data->y_offset;
    // ft_putstr_fd("y_offset: ", 2);
    // ft_putnbr_fd(data->y_offset, 2);
    // ft_putchar_fd('\n', 2);
    // ft_putstr_fd("npiece_y: ", 2);
    // ft_putnbr_fd(data->npiece_y, 2);
    // ft_putchar_fd('\n', 2);
}

void prep_piece(t_filler *data)
{
    int y;
    int x;

    y = 0;
    x = 0;
    get_y_offset(data, y, x);
    get_x_offset(data, y, x);
}