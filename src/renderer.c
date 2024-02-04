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
			if (p.x + y < 1023 && p.x + y >= 0 && p.y + x < 1023 && p.y + x >= 0)
				mlx_put_pixel(img, p.x + y, p.y + x, color);
			y++;
		}
		x++;
	}
}

void	draw_wall(mlx_image_t *img, float ray_length, int xoffset, t_ray *ray, mlx_texture_t *texture)
{
	int	x;
	int	y;
	int	line_height;
	int	line_width;
	float porcentageX;
	float porcentageY;

	x = 0;
	line_height = (HEIGHT * 7) / ray_length;
	// if (line_height > HEIGHT)
	// 	line_height = HEIGHT;
	line_width = WIDTH / (RAY_AMOUNT);
	if (!line_width)
		line_width = 1;
	while (x < line_width)
	{
		y = 0;
		if (ray->side == S_NORTH || ray->side == S_SOUTH)
			porcentageX = pourcentage_of(ray->hit.x);
		else
			porcentageX = pourcentage_of(ray->hit.y);
		while (y < line_height)
		{
			porcentageY = (float)y / (float)line_height * 100;
			int xmap = line_width * xoffset + x;
			int ymap = y + HALF_HEIGHT - line_height / 2;
			if (xmap < WIDTH && xmap >= 0 && ymap < HEIGHT && ymap >= 0)
				mlx_put_pixel(img, line_width * xoffset + x, y + HALF_HEIGHT - line_height / 2, get_color_wall(texture, porcentageX, porcentageY));
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
			else
			{
				;
				//draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap, NO_FLOOR_COL);
			}
			p.x++;
		}
		p.y++;
	}
	//printf("x: %f y: %f\n", player.pos.x, player.pos.y);
}

void	renderer(t_param *param, t_player player, t_map map, mlx_image_t *reality)
{
	t_dda	data;

	clear_img(reality);
	draw_minimap(player, map);
	init_dda(&data, player.angle);
	while (data.rays < RAY_AMOUNT)
	{
		dda(&data, player.pos, map);
		data.angle += DEGREE_STEP;
		if (data.angle > TWO_PI)
			data.angle -= TWO_PI;
		//printf("ray hit x: %f, y: %f\n", pourcentage_of(data.hit_ray.hit.x), pourcentage_of(data.hit_ray.hit.y));
		if (data.hit_ray.side == S_NORTH)
			draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, &(data.hit_ray), param->north);
		else if (data.hit_ray.side == S_SOUTH)
			draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, &(data.hit_ray), param->south);
		else if (data.hit_ray.side == S_EAST)
			draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, &(data.hit_ray), param->east);
		else
			draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, &(data.hit_ray), param->west);
		draw_line(map.minimap, data.hit_ray.hit, player.pos, 0xFFFF00FF);
		data.rays++;
	}
	draw_square(4, v2_sub(player.pos, v2_new(2, 2)), map.minimap, PLAYER_COL);
}
