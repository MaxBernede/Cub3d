/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/29 22:02:49 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/12/04 12:37:31 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vec3	vec3_multiply(t_vec3 v3, double multiplier)
{
	v3.x *= multiplier;
	v3.y *= multiplier;
	v3.z *= multiplier;
	return (v3);
}

void	put_square(int size, t_vec3 p, mlx_image_t *img, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (p.x + j < 1023 && p.x + j >= 0 && p.y + i < 1023 && p.y + i >= 0)
				mlx_put_pixel(img, p.x + j, p.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_player player, t_map map)
{
	t_vec3	p;

	p.y = 0;
	while (p.y < map.height)
	{
		p.x = 0;
		while (p.x < map.length)
		{
			if (map.map[(int)p.y][(int)p.x]  == '1')
				put_square(map.tile_size, vec3_multiply(p, map.tile_size), map.minimap, WALL_COL);
			if (ft_strchr("0NWSE", map.map[(int)p.y][(int)p.x]))
				put_square(map.tile_size, vec3_multiply(p, map.tile_size), map.minimap, FLOOR_COL);
			p.x++;
		}
		p.y++;
	}
	//printf("x: %f y: %f\n", player.pos.x, player.pos.y);
	put_square(4, player.pos, map.minimap, PLAYER_COL);
}
