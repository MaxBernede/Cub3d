#include "cub3d.h"

void	print_pos(t_vec3 vec)
{
	printf("(%.2f,%.2f,%.2f) ", vec.x, vec.y, vec.z);
}

void	print_color(t_color color)
{
	printf("colors:(%d,%d,%d) ", color.r, color.g, color.b);
}

void print_param(t_param *param)
{
	printf("Window : %d x %d\n",param->window.width, param->window.height);
	printf("\n");
	print_shapes(param->shapes);
}