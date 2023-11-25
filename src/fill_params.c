#include "cub3d.h"

// int fill_window(char **split, t_param *param)
// {
// 	if (ft_2d_arrlen(split) != 3 || ft_is_number(split[1]) || ft_is_number(split[2]))
// 		return (ERROR);
// 	if (ft_atoi_overflow(split[1], &param->window.width))
// 		return (ERROR);
// 	if (ft_atoi_overflow(split[2], &param->window.height))
// 		return (ERROR);
// 	//printf("R: %d x %d \n", param->window.width, param->window.height);
// 	return (OK);
// }

int add_param(char **split, t_param *param)
{
	char type;

	type = ft_tolower(split[0][0]);
	// if (type == 'c' && fill_camera(split, param))
	// 	return (printf(ERR_CAM), ERROR);
	if (type == 'r' && fill_window(split, param))
		return (printf(ERR_WINDOW), ERROR);
	else if (type != 'c' && type != 'a' && type != 'l' && type != 'r')
		return (printf(ERR_ADD_PARAM), ERROR);
	return (OK);
}
