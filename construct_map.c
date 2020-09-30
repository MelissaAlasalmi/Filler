#include "filler.h"

int ft_abs(int n)
{
    if (n < 0)
		n = n * -1;
    return (n);
}

int fill_heatmap(t_filler *data, int row, int column)
{
    int y;
    int x;
    int distance;
    int min;

    y = 0;
    min = 0;
    while (y <= data->map_y)
    {    
        x = 0;
        while (x <= data->map_x)
        {
            if (data->heatmap[y][x] == -2)
            {
                distance = ft_abs(x - column);
                distance += ft_abs(y - row);
                if (distance < min || min == 0)
                    min = distance;
            }
            x++;
        }
        y++;
    }
    return(min);
}

void construct_heatmap(t_filler *data)
{
    int row;
    int column;

    row = 0;
    while (row <= data->map_y)
    {    
        column = 0;
        while (column <= data->map_x)
        {
            if (data->heatmap[row][column] == 0)
                data->heatmap[row][column] = fill_heatmap(data, row, column);
            column++;
        }
        row++;
    }
    prep_piece(data);
}

int construct_map(t_filler *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!(data->heatmap = (int**)malloc(sizeof(int*) * data->map_y)))
		return (0);
    while (i < data->map_x)
    {
        if(!(data->heatmap[i] = (int*)malloc(sizeof(int) * data->map_x)))
            return(0);
        i++;
    }
    i = 0;
    while (i < data->map_y)
    {
        while (j < data->map_x)
        {
            if (data->map[i][j] == '.')
                data->heatmap[i][j] = 0;
            if (data->map[i][j] == 'o' || data->map[i][j] == 'O')
                data->heatmap[i][j] = -1;
            if (data->map[i][j] == 'x' || data->map[i][j] == 'X')
                data->heatmap[i][j] = -2;
            j++;
        }
        i++;
        j = 0;
    }
    construct_heatmap(data);
    return (0);
}