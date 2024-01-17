#include "../includes/cub3d.h"

void	clear_img(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 3;
	while (i < img->width * img->height)
	{
		if (img->pixels[j])
			img->pixels[j] = 0;
		i++;
		j += 4;
	}
}

void	draw_wall(mlx_image_t *img, float ray_length, int xoffset, uint32_t color)
{
	int	i;
	int	j;
	int	line_height;

	
	i = 0;
	line_height = (TILE_SIZE * 255) / ray_length;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	while (i < LINE_WITDH)
	{
		j = 0;
		while (j < line_height)
		{
			mlx_put_pixel(img, LINE_WITDH * xoffset + i, j + MIDDLE_SCREEN - line_height / 2, color);
			j++;
		}
		i++;
	}
}

void	renderer(t_player player, t_map map, mlx_image_t *reality)
{
	t_dda	data;

	clear_img(reality);
	init_dda(&data, player.angle);
	while (data.rays < FOV)
	{
		dda(&data, player.pos, map);
		data.angle += ONE_DEGREE;
		if (data.angle > TWO_PI)
			data.angle -= TWO_PI;
		//printf("close hit: x %f,  y %f\n", hit.x, hit.y);
		data.rays++;
		draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, 0xFF0000FF);
		draw_line(map.minimap, data.hit_ray.hit, player.pos, 0xFFFF00FF);
	}
}
