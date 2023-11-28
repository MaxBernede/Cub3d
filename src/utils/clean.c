#include "cub3d.h"

void	clean_everything(t_param *param)
{
	// free_shapes_list(param->shapes);
	ft_2dfree(param->map.map);
}