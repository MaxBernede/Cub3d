/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:37 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 20:58:35 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color_wall(mlx_texture_t *texture, float percentage_x,
		float percentage_y, double shade)
{
	uint32_t	pos_x;
	uint32_t	pos_y;
	uint32_t	pixel_index;
	t_ucolor	c;

	if (percentage_x <= 0)
		pos_x = 0;
	else
		pos_x = (uint32_t)(percentage_x * texture->width);
	if (percentage_y <= 0)
		pos_y = 0;
	else
		pos_y = (uint32_t)(percentage_y * texture->width);
	pixel_index = (pos_y * texture->width + pos_x) * texture->bytes_per_pixel;
	c.r = texture->pixels[pixel_index] * shade;
	c.g = texture->pixels[pixel_index + 1] * shade;
	c.b = texture->pixels[pixel_index + 2] * shade;
	return (ft_pixel(c.r, c.g, c.b, 255));
}

void	get_percent_x(float *percent_x, t_dda dda, double *shade)
{
	*shade = exp(-0.015 * dda.hit_ray.length);
	if (dda.hit_ray.side == S_NORTH || dda.hit_ray.side == S_SOUTH)
		*percent_x = pourcentage_of(dda.hit_ray.hit.x);
	else
	{
		*percent_x = pourcentage_of(dda.hit_ray.hit.y);
		*shade *= .8;
	}
}

void	fill_wall(t_wall *wall, float ray_len, float dda_angle, float angle)
{
	wall->height = (HEIGHT * 10) / (ray_len * cos(angle - dda_angle));
	wall->width = WIDTH / (RAY_AMOUNT);
	if (!wall->width)
		wall->width = 1;
}

void	draw_wall(t_param *param, t_dda dda)
{
	t_wall	wall;
	float	percent_x;
	int		xmap;
	int		ymap;

	wall.x = 0;
	fill_wall(&wall, dda.hit_ray.length, dda.angle, param->player.angle);
	get_percent_x(&percent_x, dda, &wall.shade);
	while (wall.x < wall.width)
	{
		wall.y = 0;
		xmap = wall.width * dda.rays + wall.x;
		while (wall.y < wall.height)
		{
			ymap = wall.y + HALF_HEIGHT - wall.height / 2;
			if (xmap < WIDTH && xmap >= 0 && ymap < HEIGHT && ymap >= 0)
				mlx_put_pixel(param->reality, xmap, ymap,
					get_color_wall(param->textures[dda.hit_ray.side],
						percent_x, (float)wall.y / (float)wall.height,
						wall.shade));
			wall.y++;
		}
		wall.x++;
	}
}
