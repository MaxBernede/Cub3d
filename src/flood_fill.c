#include "cub3d.h"

int	flood_fill(t_map map, int x, int y)
{
	int	r;

	r = 0;
	if (x < 0 || x >= map.length || y < 0 || y >= map.height
		|| map.flood[y][x] == ' ')
	{
		return (ERROR);
	}
	if (map.flood[y][x] == '1' || map.flood[y][x] == '9')
		return (OK);
	map.flood[y][x] = '9';
	//this print will show the map with the colored squares
	//print_flood(map);
	r += flood_fill(map, x, y - 1);
	r += flood_fill(map, x, y + 1);
	r += flood_fill(map, x + 1, y);
	r += flood_fill(map, x - 1, y);
	return (r);
}
