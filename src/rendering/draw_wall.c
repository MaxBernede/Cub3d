/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:37 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/09 21:24:07 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color_wall(mlx_texture_t *texture, uint32_t pos_x,
		uint32_t pos_y, double shade)
{

	uint32_t	pixel_index;
	t_ucolor	c;

	if (pos_x < 0)
		pos_x = 0;
	if (pos_y < 0)
		pos_y = 0;
	pixel_index = (pos_y * texture->width + pos_x) * texture->bytes_per_pixel;
	c.r = texture->pixels[pixel_index] * shade;
	c.g = texture->pixels[pixel_index + 1] * shade;
	c.b = texture->pixels[pixel_index + 2] * shade;
	return (ft_pixel(c.r, c.g, c.b, 255));
}

void	fill_wall(t_wall *wall, t_dda dda, int tex_width)
{
	float	tex_offset;

	wall->height = (HEIGHT * 10) / dda.ray.length;
	wall->py_step = (float)tex_width / (float)wall->height;
	if (wall->height > HEIGHT)
	{
		tex_offset = (float)(wall->height - HEIGHT) / 2.0;
		wall->height = HEIGHT;
	}
	else
		tex_offset = 0;
	wall->width = WIDTH / (RAY_AMOUNT);
	if (!wall->width)
		wall->width = 1;
	wall->shade = exp(-0.015 * dda.ray.length);
	if (dda.ray.type == X)
		wall->percent_x = pourcentage_of(dda.ray.hit.x);
	else
	{
		wall->percent_x = pourcentage_of(dda.ray.hit.y);
		wall->shade *= .8;
	}
	wall->percent_x *= (float)tex_width;
	wall->percent_y = tex_offset * wall->py_step;
}

void	draw_wall(t_param *param, t_dda dda)
{
	t_wall	wall;
	int		xmap;
	int		ymap;

	wall.y = 0;
	fill_wall(&wall, dda, param->textures[dda.ray.side]->width);
	while (wall.y < wall.height)
	{
		wall.x = 0;
		ymap = wall.y + HALF_HEIGHT - wall.height / 2;
		while (wall.x < wall.width)
		{
			xmap = wall.width * dda.rays + wall.x;
			mlx_put_pixel(param->reality, xmap, ymap,
					get_color_wall(param->textures[dda.ray.side],
						wall.percent_x, wall.percent_y, wall.shade));
			++wall.x;
		}
		wall.percent_y += wall.py_step;
		++wall.y;
	}
}
