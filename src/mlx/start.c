/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:33:19 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 18:04:12 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_background(mlx_image_t *background, t_param *param)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HALF_HEIGHT)
				mlx_put_pixel(background, x, y, param->map.ceil_color);
			else
				mlx_put_pixel(background, x, y, param->map.floor_color);
			y++;
		}
		x++;
	}
}

int	init_images(t_param *param, t_window w)
{
	param->background = mlx_new_image(param->mlx, w.width, w.height);
	if (!param->background)
		return (ERROR);
	param->reality = mlx_new_image(param->mlx, w.width, w.height);
	if (!param->reality)
		return (ERROR);
	param->map.minimap = mlx_new_image(param->mlx, param->map.length
			* TILE_SIZE, param->map.height * TILE_SIZE);
	if (!param->map.minimap)
		return (ERROR);
	return (OK);
}

int	start(t_param *param, t_window w)
{
	param->mlx = mlx_init(w.width, w.height, "cub3d", true);
	if (!param->mlx)
		return (ERROR);
	if (init_images(param, w))
		return (mlx_close_window(param->mlx), printf(ERR_IMG_CREA), ERROR);
	init_player(param->map, &param->player, param->floor);
	draw_background(param->background, param);
	render(param);
	if (mlx_image_to_window(param->mlx, param->background, 0, 0) == -1
		|| mlx_image_to_window(param->mlx, param->reality, 0, 0) == -1
		|| mlx_image_to_window(param->mlx, param->map.minimap, 0, 0) == -1)
	{
		mlx_close_window(param->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(param->mlx, my_hook, param);
	mlx_loop(param->mlx);
	mlx_terminate(param->mlx);
	return (OK);
}
