#include "cub3d.h"

void	update_minimap(t_player *player, t_map map, double dx, double dy)
{
		player->pos.x += dx;
		player->pos.y += dy;
		draw_minimap(*player, map);
}

#define WALKSPEED .3
void	my_hook(void *param)
{
	t_param	*p;

	p = param;
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
	if (mlx_is_key_down(p->mlx, MLX_KEY_UP))
	{
		p->img->instances[0].y -= 5;
		update_minimap(&p->player, p->map, 0, -WALKSPEED);
	}
	if (mlx_is_key_down(p->mlx, MLX_KEY_DOWN))
	{
		p->img->instances[0].y += 5;
		update_minimap(&p->player, p->map, 0, WALKSPEED);
	}
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
	{
		p->img->instances[0].x -= 5;
		update_minimap(&p->player, p->map, -WALKSPEED, 0);
	}
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
	{
		p->img->instances[0].x += 5;
		update_minimap(&p->player, p->map, WALKSPEED, 0);
	}
}
