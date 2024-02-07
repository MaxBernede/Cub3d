/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:37 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 14:35:20 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color_wall(mlx_texture_t *texture, float percentage_x,
		float percentage_y)
{
	uint32_t	pos_x;
	uint32_t	pos_y;
	uint32_t	pixel_index;
	t_ucolor	c;
	uint32_t	color;

	if (percentage_x <= 0)
		pos_x = 0;
	else
		pos_x = (uint32_t)(percentage_x / 100.0 * texture->width);
	if (percentage_y <= 0)
		pos_y = 0;
	else
		pos_y = (uint32_t)(percentage_y / 100.0 * texture->width);
	pixel_index = (pos_y * texture->width + pos_x) * texture->bytes_per_pixel;
	c.r = texture->pixels[pixel_index];
	c.g = texture->pixels[pixel_index + 1];
	c.b = texture->pixels[pixel_index + 2];
	color = (c.r << 24) | (c.g << 16) | (c.b << 8) | 255;
	return (color);
}

void	get_percent_x(float *percent_x, t_dda dda)
{
	if (dda.hit_ray.side == S_NORTH || dda.hit_ray.side == S_SOUTH)
		*percent_x = pourcentage_of(dda.hit_ray.hit.x);
	else
		*percent_x = pourcentage_of(dda.hit_ray.hit.y);
}

void	fill_wall(t_wall *wall, float ray_len, float dda_angle, float angle)
{
	wall->height = (HEIGHT * 6) / (ray_len * cos(angle - dda_angle));
	wall->width = WIDTH / (RAY_AMOUNT);
	if (!wall->width)
		wall->width = 1;
}

void	draw_wall(t_param *param, t_dda dda)
{
	t_wall	wall;
	int		x;
	int		y;
	float	percent_x;
	int		xmap;
	int		ymap;

	x = 0;
	fill_wall(&wall, dda.hit_ray.length, dda.angle, param->player.angle);
	get_percent_x(&percent_x, dda);
	while (x < wall.width)
	{
		y = 0;
		xmap = wall.width * dda.rays + x;
		while (y < wall.height)
		{
			ymap = y + HALF_HEIGHT - wall.height / 2;
			if (xmap < WIDTH && xmap >= 0 && ymap < HEIGHT && ymap >= 0)
				mlx_put_pixel(param->reality, xmap, ymap,
					get_color_wall(param->textures[dda.hit_ray.side],
						percent_x, (float)y / (float)wall.height * 100));
			y++;
		}
		x++;
	}
}

// void	draw_wall(t_param *param, t_dda dda)
// {
// 	t_wall	wall;
// 	float	percent_x;
// 	int		xmap;
// 	int		ymap;

// 	wall.x = 0;
// 	fill_wall(&wall, dda);
// 	get_percent_x(&percent_x, dda);
// 	while (wall.x < wall.width)
// 	{
// 		wall.y = 0;
// 		xmap = wall.width * dda.rays + wall.x;
// 		while (wall.y < wall.height)
// 		{
// 			ymap = wall.y + HALF_HEIGHT - wall.height / 2;
// 			if (xmap < WIDTH && xmap >= 0 && ymap < HEIGHT && ymap >= 0)
// 				mlx_put_pixel(param->reality, xmap, ymap,
// 					get_color_wall(param->textures[dda.hit_ray.side],
// 						percent_x, (float)wall.y / (float)wall.height * 100));
// 			wall.y++;
// 		}
// 		wall.x++;
// 	}
// }
