/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_wall.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:37 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 13:44:17 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color_wall(mlx_texture_t *texture, float percentage_x,
		float percentage_y)
{
	uint32_t	pos_x;
	uint32_t	pos_y;
	uint32_t	pixel_index;
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;
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
	r = texture->pixels[pixel_index];
	g = texture->pixels[pixel_index + 1];
	b = texture->pixels[pixel_index + 2];
	color = (r << 24) | (g << 16) | (b << 8) | 255;
	return (color);
}
