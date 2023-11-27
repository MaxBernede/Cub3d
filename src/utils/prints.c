#include "cub3d.h"


#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_WHITE "\x1b[37m"
#define ANSI_RESET "\x1b[0m"


void	print_pos(t_vec3 vec)
{
	printf("(%.2f,%.2f,%.2f) ", vec.x, vec.y, vec.z);
}

void	print_color(t_color color)
{
	printf("colors:(%d,%d,%d) ", color.r, color.g, color.b);
}

void print_flood(t_map map)
{
	int y;
	int x;

	y = 0;
	printf("\n");
	while (y < map.height)
	{
		x = 0;
		while (x < map.length)
		{
			if (map.flood[y][x] == '1')
				printf(ANSI_RED "■" ANSI_RESET);
			else if (map.flood[y][x] == '9')
				printf(ANSI_GREEN "■" ANSI_RESET);
			else if (map.flood[y][x] == '0')
				printf(ANSI_WHITE "■" ANSI_RESET);
			else
				printf("■");
			++x;
		}
		printf("\n");
		++y;
	}
}