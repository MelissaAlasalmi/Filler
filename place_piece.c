#include "filler.h"

static int remove_offset(t_filler *data, int row, int column)
{
    int i;
    int j;

    i = 0;
    j = 0;
	if (!(data->npiece = (int**)malloc(sizeof(int*) * (data->piece_y - data->row_offset))))
		return (0);
    while (column < data->piece_x)
    {
        if(!(data->npiece[column] = (int*)malloc(sizeof(int) * (data->map_x- data->column_offset))))
            return(0);
        column++;
    }
    row = data->row_offset; //set's place for original piece to compare
    column = data->column_offset; //set's place for original piece to compare
    while (row < data->piece_y)
	{
        while (data->piece[row][column] != '\0')
        {
            if(data->piece[row][column] == '*')
                data->npiece[i][j] = -1;
            else
                data->npiece[i][j] = 0;
            column++;
            j++;
        }
        row++;
        i++;
        column = data->column_offset;
        j = 0;
    }
    return (1);
}

void get_x_offset(t_filler *data, int row, int column)
{
    int temp;
    int x_offset;

    temp = 0;
    x_offset = 0;   
    while (row < data->piece_y)
	{
		while (data->piece[row][column] == '.')
        {
            temp++;
            column++;
        }
        if (temp < x_offset || x_offset == 0)
            x_offset = temp;
        temp = 0;
        column = 0;
		row++;
	}
    data->column_offset = x_offset;
}

void get_y_offset(t_filler *data, int row, int column)
{
    int y_offset;

    y_offset = 0;
    while (row < data->piece_y)
	{
        while (data->piece[row][column] == '.')
            column++;
        if (data->piece[row][column] == '\0')
        {
            y_offset++;
            column = 0;
            row++;
        }
        else
            break ;
    }
    data->row_offset = y_offset;
}

void place_piece(t_filler *data)
{
    int row;
    int column;

    row = 0;
    column = 0;
    get_y_offset(data, row, column);
    get_x_offset(data, row, column);
    remove_offset(data, row, column);

}