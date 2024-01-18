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
	line_height = HEIGHT / ray_length * 4;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	printf("Line Width: %d\n", LINE_WITDH * RAY_AMOUNT);
	while (i < LINE_WITDH)
	{
		j = 0;
		while (j < line_height)
		{
			mlx_put_pixel(img, LINE_WITDH * xoffset + i, j + HALF_HEIGHT - line_height / 2, color);
			j++;
		}
		i++;
	}
}

void	renderer(t_player player, t_map map, mlx_image_t *reality)
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
		//printf("close hit: x %f,  y %f\n", data.hit_ray.x, daya.hit_ray.y);
		if (data.xray.length < data.yray.length)
			draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, 0xAF0000FF);
		else
			draw_wall(reality, data.hit_ray.length * cos(player.angle - data.angle), data.rays, 0x9F0000FF);
		draw_line(map.minimap, data.hit_ray.hit, player.pos, 0xFFFF00FF);
		data.rays++;
	}
}
