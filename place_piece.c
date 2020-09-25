#include "filler.h"

// void remove_offset(t_filler *data)
// {


// }

void place_piece(t_filler *data)
{
    int i;
    int j;
    int temp;
    int y_offset;
    int x_offset;

    i = 0;
    j = 0;
    temp = 0;
    y_offset = 0;
    x_offset = 0;
    while (data->piece[i] != NULL)
	{
        while (data->piece[i][j] == '.')
            j++;
        if (data->piece[i][j] == '\0')
        {
            y_offset++;
            j = 0;
            i++;
        }
        else
            break ;
    }
    i = 0;
    j = 0;
    while (data->piece[i] != NULL)
	{
		while (data->piece[i][j] == '.')
        {
            temp++;
            j++;
        }
        if (temp < x_offset || x_offset == 0)
            x_offset = temp;
        temp = 0;
        j = 0;
		i++;
	}
    data->row_offset = y_offset;
    data->column_offset = x_offset;
}