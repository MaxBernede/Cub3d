#include "cub3d.h"
#include <math.h>

bool	movement_key_down(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W)
		|| mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_A)
		||  mlx_is_key_down(mlx, MLX_KEY_D))
	{
		return (true);
	}
	return (false);
}

void	move_player(t_player *player, char **map, int direction, double dt)
{
	t_vec2	new_pos;
	t_vec2	offset;
	int		mapo;

	if (dt > .25)
		dt = .25;
	if (player->delta.x < 0)
		offset.x = -1;
	else
		offset.x = 1;
	if (player->delta.y < 0)
		offset.y = -1;
	else
		offset.y = 1;
	new_pos.x = player->pos.x + player->delta.x * direction * dt;
	new_pos.y = player->pos.y + player->delta.y * direction * dt;
	mapo = (new_pos.x + offset.x * direction) / TILE_SIZE;
	if (ft_strchr("0NSEW", map[(int)((player->pos.y + 1) / TILE_SIZE)][mapo])
			&& ft_strchr("0NSEW", map[(int)((player->pos.y - 1) / TILE_SIZE)][mapo]))
		player->pos.x = new_pos.x;
	mapo = (new_pos.y + offset.y * direction) / TILE_SIZE;
	if (ft_strchr("0NSEW", map[mapo][(int)((player->pos.x + 1) / TILE_SIZE)])
			&& ft_strchr("0NSEW", map[mapo][(int)((player->pos.x - 1) / TILE_SIZE)]))
		player->pos.y = new_pos.y;
}

void	change_player_angle(t_player *player, int direction, double dt)
{
	player->angle += TURNSPEED * direction * dt;
	if (player->angle < 0)
		player->angle += TWO_PI;
	else if (player->angle > TWO_PI)
		player->angle -= TWO_PI;
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
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
		//printf("player x: %f, player y: %f player angle: %f\n", p->player.pos.x, p->player.pos.y, p->player.angle);
		renderer(param, p->player, p->map, p->wall_img);
	}
}
