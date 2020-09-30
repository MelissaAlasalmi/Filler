#include "filler.h"

void save_coords(t_filler *data, int y, int x)
{
    int temp_sum;
    int coord_y;
    int coord_x;
    int y_temp;
    int x_temp;

    temp_sum = 0;
    coord_y = 0;
    coord_x = 0;
    data->sum = 0;
    y_temp = y + data->npiece_y;
    x_temp = x + data->npiece_x;
    while (y < y_temp) //parses thru valid piece area to gather data
    {
        while (x < x_temp) //parses thru vajid piece area to gather data
        {
            ft_putnbr_fd(data->heatmap[y][x], 2);
            temp_sum = temp_sum + data->heatmap[y][x];
            if (data->heatmap[y][x] == -1)
            {
             coord_y = y;   
                coord_x = x;
            }   
            x++;
        }
        y++;
    }
    if (temp_sum < data->sum)
    {
        data->sum = temp_sum;
        data->coord_y = coord_y;
        data->coord_x = coord_x;
    }
}

int scan_piece_area(t_filler *data, int y, int x)
{
    int count;
    int x_reset;
    int y_temp;
    int x_temp;

    count = 0;
    x_reset = x;
    y_temp = y + data->npiece_y;
    x_temp = x + data->npiece_x;
    while (y < y_temp) //parses thru map alongside piece values
    {
        x = x_reset;
        while (x < x_temp) //parses thru map alongside piece values
        {
            if (data->heatmap[y][x] == -1)
            {
                count++;
                x++;
            }
            else if (data->heatmap[y][x] == -2)
            {
                count = 2;
                break ;
            }
            else
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
    while (y <= (data->map_y - data->npiece_y)) //parses thru whole playable map
    {
        x = 0;
        while (x <= (data->map_x - data->npiece_x)) //parses thru whole playable map
        {
            count = scan_piece_area(data, y, x);
            if (count == 1)
                save_coords(data, y, x);
            x++;
        }
        y++;
    }
}
