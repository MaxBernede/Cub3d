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

void	move_player(t_player *player, char **map, int direction)
{
	t_vec2	offset;
	int		mapo;
	int		map_index;

	if (player->delta.x < 0)
		offset.x = 2;
	else
		offset.x = -2;
	if (player->delta.y < 0)
		offset.y = 2;
	else
		offset.y = -2;
	map_index = player->pos.y / TILE_SIZE;
	mapo = (player->pos.x + offset.x * -direction) / TILE_SIZE;
	if (ft_strchr("0NSEW", map[map_index][mapo]))
		player->pos.x += player->delta.x * direction;
	map_index = player->pos.x / TILE_SIZE;
	mapo = (player->pos.y + offset.y * -direction) / TILE_SIZE;
	if (ft_strchr("0NSEW", map[mapo][map_index]))
		player->pos.y += player->delta.y * direction;
}

void	change_player_angle(t_player *player, int direction)
{
	player->angle += TURNSPEED * direction;
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
			move_player(&p->player, p->map.map, -1);
		if (mlx_is_key_down(p->mlx, MLX_KEY_S))
			move_player(&p->player, p->map.map, 1);
		if (mlx_is_key_down(p->mlx, MLX_KEY_A))
			change_player_angle(&p->player, -1);
		if (mlx_is_key_down(p->mlx, MLX_KEY_D))
			change_player_angle(&p->player, 1);
		//printf("player x: %f, player y: %f player angle: %f\n", p->player.pos.x, p->player.pos.y, p->player.angle);
		draw_minimap(p->player, p->map);
		DDA(p->player, p->map);
	}
}
