#include "../../includes/cub3d.h"
#include <stdint.h>
#include <stdio.h>

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	init_player(t_map map, t_player *player)
{
	char	direction;
	int		x;
	int		y;

	get_char_start(map, &y, &x);
	direction = map.map[y][x];
	printf("%d, %d, %c\n", x, y, direction);
	if (direction == 'N')
		player->angle = HALF_PI;
	else if (direction == 'W')
		player->angle = PI;
	else if (direction == 'S')
		player->angle = PI + HALF_PI;
	else
		player->angle = 0;
	player->pos.x = x * TILE_SIZE + TILE_SIZE * 0.5;
	player->pos.y = y * TILE_SIZE + TILE_SIZE * 0.5;
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
}

void	draw_background(mlx_image_t *background, uint32_t floor_color, uint32_t roof_color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH / 2)
	{
		y = 0;
		while (y < HALF_HEIGHT)
		{
			mlx_put_pixel(background, x, y, floor_color);
			y++;
		}
		x++;
	}
	while (x < WIDTH)
	{
		y = HALF_HEIGHT + 1;
		while (y < HEIGHT)
		{
			mlx_put_pixel(background, x, y, roof_color);
			y++;
		}
		x++;
	}
}

int	start(t_param *param, t_window w)
{
	param->mlx = mlx_init(w.width, w.height, "cub3d", true);
	if (!param->mlx)
		return (ERROR);
	param->map.minimap = mlx_new_image(param->mlx, w.width, w.height);
	if (!param->map.minimap)
		return (mlx_close_window(param->mlx), ERROR);
	param->wall_img = mlx_new_image(param->mlx, w.width, w.height);
	if (!param->wall_img)
		return (mlx_close_window(param->mlx), ERROR);
	param->background = mlx_new_image(param->mlx, w.width, w.height);
	if (!param->background)
		return (mlx_close_window(param->mlx), ERROR);
	init_player(param->map, &param->player);
	draw_background(param->background, ft_pixel(param->floor.r, param->floor.g, param->floor.b, 255), ft_pixel(param->ceiling.r, param->ceiling.g, param->ceiling.b, 255));
	renderer(param->player, param->map, param->wall_img);
	/*for (int y = 0; y < w.height; ++y)
	{
		for (int x = 0; x < w.width; ++x)
		{
			int r = x / 2;
			int g = y / 2;
			int b = 0;
			mlx_put_pixel(param->wall_img, x, y, ft_pixel(r, g, b, 255));
		}
	} */
	if (mlx_image_to_window(param->mlx, param->wall_img, 0, 0) == -1
		|| mlx_image_to_window(param->mlx, param->map.minimap, 0, 0) == -1
		|| mlx_image_to_window(param->mlx, param->background, 0, 0) == -1)
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
