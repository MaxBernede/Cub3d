/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:35:16 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/09 20:37:20 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		++i;
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
			if (p.x + y < img->width && p.x + y >= 0 && p.y + x < img->height
				&& p.y + x >= 0)
				mlx_put_pixel(img, p.x + y, p.y + x, color);
			++y;
		}
		++x;
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
			if (map.map[(int)p.y][(int)p.x] == '1')
				draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap,
					WALL_COL);
			else if (ft_strchr("0NWSE", map.map[(int)p.y][(int)p.x]))
				draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap,
					map.floor_color);
			else if (map.map[(int)p.y][(int)p.x] == 'D')
				draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap,
					DOOR_COL);
			else if (map.map[(int)p.y][(int)p.x] == 'K')
				draw_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap,
					KEY_COL);
			++p.x;
		}
		++p.y;
	}
}

void	render(t_param *p)
{
	t_dda			data;
	static float	degree_step = ONE_DEGREE / SHARPNESS;

	clear_img(p->reality);
	draw_minimap(p->player, p->map);
	init_dda(&data, p->player.angle - (ONE_DEGREE * FOV) / 2);
	while (data.rays < RAY_AMOUNT)
	{
		dda(&data, &p->player, p->map, "1D");
		data.angle += degree_step;
		if (data.angle > TWO_PI)
			data.angle -= TWO_PI;
		draw_wall(p, data);
		draw_line(p->map.minimap, data.ray.hit,
			p->player.pos, RAY_COL);
		data.rays++;
	}
	draw_square(4, v2_sub(p->player.pos, v2_new(2, 2)),
		p->map.minimap, PLAYER_COL);
}
