#include "filler.h"

void save_coords(t_filler *data, int y, int x)
{
    int temp_sum;
    int y_temp;
    int x_temp;
    int x_reset;
    int y_reset;

    temp_sum = 0;
    y_temp = y + data->npiece_y;
    x_temp = x + data->npiece_x;
    x_reset = x;
    y_reset = y;
    while (y == 0 || y < y_temp)
    {
        x = x_reset;
        while (x == 0 || x < x_temp)
        {
            temp_sum = temp_sum + data->heatmap[y][x];
            x++;
        }
        y++;
    }
    if (temp_sum < data->sum || data->sum == 0)
    {
        data->sum = temp_sum;
        data->coord_y = y_reset;
        data->coord_x = x_reset;
    }
    ft_putstr_fd("coord_y: ", 2);
    ft_putnbr_fd(data->coord_y, 2);
    ft_putchar_fd('\n', 2);
    ft_putstr_fd("coord_x: ", 2);
    ft_putnbr_fd(data->coord_x, 2);
    ft_putchar_fd('\n', 2);
}

int check_valid(t_filler *data, int y, int x, int j, int i)
{
    int y_temp;
    int x_temp;
    int x_reset;

    y_temp = y + data->npiece_y;
    x_temp = x + data->npiece_x;
    x_reset = x;
    ft_putstr_fd("in check valid with - ", 2);
    ft_putnbr_fd(y, 2);
    ft_putchar_fd(' ', 2);
    ft_putnbr_fd(x, 2);
    ft_putchar_fd('\n', 2);
    while (y < y_temp) // 4 && 6
    {
        x = x_reset;
        i = 0;
        while (x < x_temp) // 9 && 10
        {
            ft_putstr_fd("check coord - ", 2);
            ft_putnbr_fd(y, 2);
            ft_putchar_fd(' ', 2);
            ft_putnbr_fd(x, 2);
            ft_putchar_fd('\n', 2);
            if (data->heatmap[y][x] == -1)
            {
                if(data->piece[j][i] == '.')
                {
                    ft_putstr_fd("swing and miss!", 2);
                    ft_putchar_fd('\n', 2);
                    return(1); 
                }
            }
            i++;
            x++;
        }
        y++;
        j++;
    }
    ft_putstr_fd("swing and hit!", 2);
    ft_putchar_fd('\n', 2);
    return(0);
}

int scan_piece_area(t_filler *data, int y, int x)
{
    int count; //counts the number of p1 and p1 occupied coords
    int x_reset; //keeps track of the current coord from the first loop
    int y_temp;
    int x_temp;

    count = 0;
    x_reset = x;
    y_temp = y + data->npiece_y;
    x_temp = x + data->npiece_x;
    ft_putstr_fd("in scan with - ", 2);
    ft_putnbr_fd(y, 2);
    ft_putchar_fd(' ', 2);
    ft_putnbr_fd(x, 2);
    ft_putchar_fd('\n', 2);
    while (y < y_temp)
    {
        x = x_reset;
        while (x < x_temp)
        {
            if ( data->heatmap[y][x] == -2)
            {
                count = 2;
                break ;
            }
            if (data->heatmap[y][x] == -1)
                count++;
            x++;
        }
        y++;
    }
    return(count);
}

void place_piece(t_filler *data)
{
    int y;
    int x;
    int count;

    y = 0;
    while (y <= (data->map_y - data->npiece_y))
    {
        x = 0;
        while (x <= (data->map_x - data->npiece_x))
        {
            count = scan_piece_area(data, y, x);
            ft_putstr_fd("count: ", 2);
            ft_putnbr_fd(count, 2);
            ft_putchar_fd('\n', 2);
            if (count == 1)
            {
                if (check_valid(data, y, x, data->y_offset, data->x_offset) == 0)
                    save_coords(data, y, x);
            }
            x++;
        }
        y++;
    }
}
