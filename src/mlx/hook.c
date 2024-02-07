/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:32:59 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 18:04:34 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

bool	movement_key_down(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D))
	{
		return (true);
	}
	return (false);
}

void	my_hook(void *param)
{
	t_param	*p;

	p = param;
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
	else if (movement_key_down(p->mlx))
	{
		if (mlx_is_key_down(p->mlx, MLX_KEY_W))
			move_player(&p->player, p->map.map, -1, p->mlx->delta_time);
		if (mlx_is_key_down(p->mlx, MLX_KEY_S))
			move_player(&p->player, p->map.map, 1, p->mlx->delta_time);
		if (mlx_is_key_down(p->mlx, MLX_KEY_A))
			change_player_angle(&p->player, -1, p->mlx->delta_time);
		if (mlx_is_key_down(p->mlx, MLX_KEY_D))
			change_player_angle(&p->player, 1, p->mlx->delta_time);
		render(param);
	}
}
