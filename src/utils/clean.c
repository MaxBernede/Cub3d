/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:28:44 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/21 17:36:34 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_textures(t_param *param)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (param->textures[i])
			mlx_delete_texture(param->textures[i]);
		i++;
	}
}

void	clean_everything(t_param *param)
{
	ft_2dfree(param->map.map);
	ft_2dfree(param->map.flood);
	clean_textures(param);
	if (param->reality)
		mlx_delete_image(param->mlx, param->reality);
	if (param->map.minimap)
		mlx_delete_image(param->mlx, param->map.minimap);
	if (param->background)
		mlx_delete_image(param->mlx, param->background);
}
