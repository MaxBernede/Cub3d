/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:28:44 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/16 17:19:23 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_textures(t_param *param)
{
	int	i;

	i = 0;
	while (i < 6)
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
}
