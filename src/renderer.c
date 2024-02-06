#include "../includes/cub3d.h"

void	clear_img(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	pixels;

	i = 0;
	j = 3;
	pixels = img->width * img->height;
	while (i < pixels)
	{
		if (img->pixels[j])
			img->pixels[j] = 0;
		i++;
		j += 4;
	}
}

void	draw_square(int size, t_vec2 p, mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			if (p.x + y < img->width && p.x + y >= 0 && p.y + x < img->height && p.y + x >= 0)
				mlx_put_pixel(img, p.x + y, p.y + x, color);
			y++;
		}
		x++;
	}
}

void	draw_wall(t_param *param, t_dda dda)
{
	int	x;
	int	y;
	int	wall_height;
	int	wall_width;
	float percentageX;

	x = 0;
	wall_height = (HEIGHT * 6) / (dda.hit_ray.length * cos(param->player.angle - dda.angle));
	wall_width = WIDTH / (RAY_AMOUNT);
	if (!wall_width)
		wall_width = 1;
	if (dda.hit_ray.side == S_NORTH || dda.hit_ray.side == S_SOUTH)
		percentageX = pourcentage_of(dda.hit_ray.hit.x);
	else
		percentageX = pourcentage_of(dda.hit_ray.hit.y);
	while (x < wall_width)
	{
		y = 0;
		int xmap = wall_width * dda.rays + x;
		while (y < wall_height)
		{
			int ymap = y + HALF_HEIGHT - wall_height / 2;
			if (xmap < WIDTH && xmap >= 0 && ymap < HEIGHT && ymap >= 0)
				mlx_put_pixel(param->reality, xmap, ymap, get_color_wall(param->textures[dda.hit_ray.side], percentageX, (float)y / (float)wall_height * 100));
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_player player, t_map map)
{
	t_vec2	p;

	p.y = 0;
	while (p.y < map.height)
	{
		p.x = 0;
		while (p.x < map.length)
		{
			if (map.map[(int)p.y][(int)p.x]  == '1')
				draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap, WALL_COL);
			else if (ft_strchr("0NWSE", map.map[(int)p.y][(int)p.x]))
				draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap, map.floor_color);
			p.x++;
		}
		p.y++;
	}
	//printf("x: %f y: %f\n", player.pos.x, player.pos.y);
}

void	renderer(t_param *param)
{
	t_dda	data;

	clear_img(param->reality);
	draw_minimap(param->player, param->map);
	init_dda(&data, param->player.angle);
	while (data.rays < RAY_AMOUNT)
	{
		dda(&data, param->player.pos, param->map);
		data.angle += DEGREE_STEP;
		if (data.angle > TWO_PI)
			data.angle -= TWO_PI;
		//printf("ray hit x: %f, y: %f\n", pourcentage_of(data.hit_ray.hit.x), pourcentage_of(data.hit_ray.hit.y));
		draw_wall(param, data);
		draw_line(param->map.minimap, data.hit_ray.hit, param->player.pos, 0xFFFF00FF);
		data.rays++;
	}
	draw_square(4, v2_sub(param->player.pos, v2_new(2, 2)), param->map.minimap, PLAYER_COL);
}
