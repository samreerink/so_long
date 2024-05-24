/*
check top and bottom row for '1'
check start and end for '1'
*/
int check_walls(t_map *m)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while(m->arr[0][x] && m->arr[m->rows-1][x])
    {
        if (m->arr[0][x] != '1' || m->arr[m->rows-1][x] != '1')
            return 1;
        x++;
    }
    while(y < m->rows)
    {
        if (m->arr[y][0] != '1' || m->arr[y][m->colums-1] != '1')
            return 1;
        y++;
    }
    return 0;
}

/*
get the x and y position of the player 
*/
void player_location(char **arr, int *px, int *py)
{
    int x;
    int y;

    y = 0;
    while(arr[y][0])
    {
        x = 0;
        while(arr[y][x])
        {
            if (arr[y][x] == 'P')
            {
                *px = x;
                *py = y;
                return ;
            }
            x++;
        }
        y++;
    }
}

/*
replace all non '1' with 'P' that are reachable
*/
void flood_fill(char **arr, int x, int y)
{
    if (arr[y][x] == '1' || arr[y][x] == 'W')
        return ;
    arr[y][x] = 'W';
    flood_fill(arr, x-1, y);
    flood_fill(arr, x+1, y);
    flood_fill(arr, x, y-1);
    flood_fill(arr, x, y+1);
}

/*
check for collectables and exit
*/
int flood_check(char **arr)
{
    int x;
    int y;

    y = 0;
    while(arr[y][0])
    {
        x = 0;
        while(arr[y][x])
        {
            char c = arr[y][x];
            if(c!='0' && c!='1' && c!='W' && c!='P')
                return 1;
            x++;
        }
        y++;
    }
    return 0;
}

/*
check walls for 1
floodfill a copy of map_array
check if(!(c=='0'||c=='1'||c=='P'))
*/
int error_check_map(t_map *m)
{
    char    **map;
    int     px;
    int     py;

    if (check_walls(t_map *m))
        return 1;
    map = ft_copy_array(m->map_array);
    if (!map)
        error_exit("copy map error", NULL);
    player_location(t_map *m, &px, &py);
    flood_fill(map, px, py);
    if (flood_check)
        return 1;
    return 0;
}
