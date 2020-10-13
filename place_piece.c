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
    while (y < y_temp)
    {
        x = x_reset;
        while (x < x_temp)
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
    while (y < y_temp)
    {
        x = x_reset;
        while (x < x_temp)
        {
            if (data->heatmap[y][x] == -1 && x < data->extra)
            {
                count = 2;
                break ;
            }
            else if (data->heatmap[y][x] == -1 && x >= data->extra)
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
    while (y <= (data->map_y - data->npiece_y))
    {
        x = 0;
        while (x <= (data->map_x - data->npiece_x))
        {
            count = scan_piece_area(data, y, x);
            if (count == 1)
                save_coords(data, y, x);
            x++;
        }
        y++;
    }
}
