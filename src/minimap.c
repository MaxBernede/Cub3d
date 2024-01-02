/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 22:02:49 by bjacobs           #+#    #+#             */
/*   Updated: 2023/12/25 20:58:46 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_square(int size, t_vec2 p, mlx_image_t *img, uint32_t color)
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
	t_vec2	p;

	p.y = 0;
	put_square((TILE_SIZE) * map.height, v2_new(0, 0), map.minimap, 0x808080FF);
	while (p.y < map.height)
	{
		p.x = 0;
		while (p.x < map.length)
		{
			if (map.map[(int)p.y][(int)p.x]  == '1')
				put_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap, WALL_COL);
			else if (ft_strchr("0NWSE", map.map[(int)p.y][(int)p.x]))
				put_square(TILE_SIZE, v2_mult(p, TILE_SIZE), map.minimap, FLOOR_COL);
			p.x++;
		}
		p.y++;
	}
	put_square(4, player.pos, map.minimap, PLAYER_COL);
}
