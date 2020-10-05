#include "filler.h"

void get_x_offset(t_filler *data, int y, int x)
{
    int x_offset;
    int offset_temp;

    x_offset = 0;
    offset_temp = 0;
    y = y + data->y_offset;
    while (y < data->piece_y)
	{
        x = 0;
        while (x < data->piece_x)
        {
            if (data->piece[y][x] == '.')
            {
                while (data->piece[y][x] == '.')
                {
                    offset_temp++;
                    x++;
                }
            }
            else
                break ;
        }
        if (offset_temp > x_offset)
            x_offset = offset_temp;
        offset_temp = 0;
        y++;
    }
    data->x_offset = x_offset;
    data->npiece_x = data->piece_x - data->x_offset;
}

void get_y_offset(t_filler *data, int y, int x)
{
    int y_offset;

    y_offset = 0;
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
}

void prep_piece(t_filler *data)
{
    int y;
    int x;

    y = 0;
    x = 0;
    get_y_offset(data, y, x);
    get_x_offset(data, y, x);
    place_piece(data);
}