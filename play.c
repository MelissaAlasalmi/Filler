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