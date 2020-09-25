#include "filler.h"

// void remove_offset(t_filler *data)
// {


// }

void place_piece(t_filler *data)
{
    int i;
    int j;
    int temp;
    int min;

    i = 0;
    j = 0;
    temp = 0;
    min = 0;
    while (data->piece[i] != NULL)
	{
        printf("min:%d\n", min);
		while (data->piece[i][j] == '.')
        {
            temp++;
            if (temp < min || min == 0)
                min = temp;
            j++;
        }
        printf("min:%d\n", min);
		i++;
	}
}