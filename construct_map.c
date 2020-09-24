#include "filler.h"
#include <stdio.h>

// void return_coordnates(t_filler *map)
// {
// 	ft_putnbr(map->p1_y);
// 	ft_putchar(' ');
// 	ft_putnbr(map->p1_x);
// 	ft_putchar('\n');
// }

void fill_heatmap(t_filler *data, int x)
{
    int i; // int line
    int j; // int stored in coords
    int k; // value to fill into slot(s) left of opponent
    int l; // keeps track of how many spaces need to be filled left of opponent

    i = 0;
    j = 0;
    k = 1;
    l = 0;
    printf("here");
    while (l < data->map_x && data->heatmap[i][l] != -100)
        l++;
    while (j < data->map_x)
    {
        if (data->heatmap[i][j] == -100)
        {
            j--;
            data->heatmap[i][j] = k;
            k++;
            j--;
            while (k > data->heatmap[i][j] && k <= l)
            {
                data->heatmap[i][j] = k;
                k++;
                j--;
            }
            j = j + k;
            while(data->heatmap[i][j] == -100)
            {
                data->heatmap[i][j] = x;
                j++;
            }
            k = 1;
            while (j < data->map_x)
            {
                data->heatmap[i][j] = k;
                k++;
                j++;
            }
        }
    }
}

void construct_heatmap(t_filler *data)
{
    int i; // int line
    int j; // int stored in coords
    int k; // value to fill into slot(s) left of opponent
    int l; // keeps track of how many spaces need to be filled left of opponent
    int m; // keeps track of offset to fill into line above the opponent
    int x;

    i = 0;
    j = 0;
    k = 1;
    l = 0;
    m = 0;
    x = 1;

    while (i < data->map_y)
    {
        while (l < data->map_x && data->heatmap[i][l] != -100)
            l++;
        while (j < data->map_x)
        {
            if (data->heatmap[i][j] == -100)
            {
                j--;
                data->heatmap[i][j] = k;
                k++;
                j--;
                while (k > data->heatmap[i][j] && k <= l)
                {
                    data->heatmap[i][j] = k;
                    k++;
                    j--;
                }
                j = j + k;
                while(data->heatmap[i][j] == -100)
                {
                    data->heatmap[i][j] = 0;
                    j++;
                }
                k = 1;
                while (j < data->map_x)
                {
                    data->heatmap[i][j] = k;
                    k++;
                    j++;
                }
                m = i - 1; //set m to one line above
                while (data->heatmap[m] >= 0)
                {
                    data->heatmap[m][l] = -100;
                    fill_heatmap(data, x);
                    x++;
                    m--;
                }
            }
            j++;
        }
        i++;
        j = 0;
        k = 0;
        l = 0;
        m = 0;
        x = 0;
    }

    printf("new heatmap:\n");
    i = 0;
    j = 0;
    while (i < data->map_y)
    {
        while (j < data->map_x)
        {
            if (data->heatmap[i][j] < 100)
            {
                if (data->heatmap[i][j] < 10)
                    ft_putchar_fd(' ', 2);
                ft_putchar_fd(' ', 2);
            }
            ft_putnbr_fd(data->heatmap[i][j], 2);
            ft_putchar_fd('|', 2);
            j++;
        }
        ft_putchar_fd('\n', 2);
        i++;
        j = 0;
    }
}

int construct_map(t_filler *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!(data->heatmap = (int**)malloc(sizeof(int*) * data->map_y + 1)))
		return (0);
    while (i < data->map_x)
    {
        if(!(data->heatmap[i] = (int*)malloc(sizeof(int) * (data->map_x + 1))))
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
                data->heatmap[i][j] = 100;
            if (data->map[i][j] == 'x' || data->map[i][j] == 'X')
                data->heatmap[i][j] = -100;
            j++;
        }
        i++;
        j = 0;
    }

    printf("heatmap:\n");
    i = 0;
    j = 0;
    while (i < data->map_y)
    {
        while (j < data->map_x)
        {
            ft_putnbr_fd(data->heatmap[i][j], 2);
            j++;
        }
        ft_putchar_fd('\n', 2);
        i++;
        j = 0;
    }
    ft_putchar_fd('\n', 2);
    construct_heatmap(data);
    return (0);
}