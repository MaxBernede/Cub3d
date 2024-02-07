/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_datas.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:49:46 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 16:17:07 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	floor_ceiling(int type, char *arg, t_param *p)
{
	if (type == FLOOR && is_colors(arg, &p->floor.r, &p->floor.g, &p->floor.b))
		return (printf(ERR_FILL_COLORS), ERROR);
	if (type == CEILING && is_colors(arg, &p->ceiling.r, &p->ceiling.g,
			&p->ceiling.b))
		return (printf(ERR_FILL_COLORS), ERROR);
	if (type == FLOOR)
		p->map.floor_color = ft_pixel(p->floor.r, p->floor.g, p->floor.b, 90);
	if (type == CEILING)
		p->map.ceil_color = ft_pixel(p->ceiling.r, p->ceiling.g,
				p->ceiling.b, 255);
	return (OK);
}

int	fill_texture(mlx_texture_t **texture, char *s)
{
	*texture = mlx_load_png(s);
	if (!(*texture))
		return (ERROR);
	return (OK);
}
