/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:32:59 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/10 23:47:47 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	action_key_down(mlx_t *mlx)
{
	return (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D)
		|| mlx_is_key_down(mlx, MLX_KEY_E));
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	static double	prev_x = 0;
	double			dx;
	t_param			*p;

	if (prev_x)
		dx = xpos - prev_x;
	else
		dx = 0;
	p = (t_param*)param;
	if (!mlx_is_key_down(p->mlx, MLX_KEY_LEFT_ALT))
	{
		change_player_angle(&p->player, dx * MOUSESPEED, p->mlx->delta_time);
		mlx_set_mouse_pos(p->mlx, 512, 256);
	}
	prev_x = xpos;
}

void	my_hook(void *param)
{
	t_param	*p;

	p = param;
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
	if (mlx_is_key_down(p->mlx, MLX_KEY_W))
		move_player_y(&p->player, p->map.map, -1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_S))
		move_player_y(&p->player, p->map.map, 1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_D))
		move_player_x(&p->player, p->map.map, -1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_A))
		move_player_x(&p->player, p->map.map, 1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
		change_player_angle(&p->player, -1 * TURNSPEED, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
		change_player_angle(&p->player, 1 * TURNSPEED, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_E))
		open_door(&p->player, &p->map);
	render(param);
}
