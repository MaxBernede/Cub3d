/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_datas.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:49:46 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/08 13:57:15 by maxb          ########   odam.nl         */
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

int	fill_texture(mlx_texture_t **texture, xpm_t **xpm, char *s)
{
	if (endswith(s, ".xpm"))
	{	
		;
		// void *img_ptr;

		// img_ptr = mlx_xpm_file_to_image(g_mlx, s, &(*xpm)->width, &(*xpm)->height);
		// *xpm = mlx_load_xpm42(s);
        // if (*xpm == NULL) 
		// 	return (printf("Error: Unable to load XPM file %s\n", s), ERROR);
        // *texture = &(*xpm)->texture;
	} 	
	else if (endswith(s, ".png"))
		*texture = mlx_load_png(s);
	if (!(*texture))
		return (ERROR);
	return (OK);
}
