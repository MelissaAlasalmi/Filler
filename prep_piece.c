#include "filler.h"

void get_x_offset(t_filler *data, int y, int x)
{
    int x_offset;

    x_offset = 0;   
    while (y < data->piece_y)
	{
        if (x_offset == 0)
        {
            while (x < data->piece_x)
            {
                if (data->piece[y][x] == '.')
                    x_offset++;
                else
                    break ;   
                x++;
            }
            if (x_offset == data->piece_x)
                x_offset = 0;
            x = 0;
            y++;
        }
        else
        {
            while (x < x_offset)
            {
                if (data->piece[y][x] == '*')
                {
                    x_offset--;
                    break ;
                }
                x++;
            }
            y++;
        }
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