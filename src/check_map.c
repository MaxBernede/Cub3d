/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:52:04 by maxb          #+#    #+#                 */
/*   Updated: 2023/12/04 17:56:08 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check if the char is != than 1 time
int	check_char(t_map map)
{
	int	found;
	int	x;
	int	y;

	found = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.length)
		{
			if (ft_strchr("NSEW", map.map[y][x]))
				found += 1;
			++x;
		}
		++y;
	}
	if (found != 1)
		return (ERROR);
	return (OK);
}

int	check_map(t_param *param)
{
	int	x;
	int	y;

	if (check_char(param->map))
		return (printf(ERR_CHARACTER), ERROR);
	if (get_char_start(param->map, &y, &x))
		return (printf(ERR_START_POS), ERROR);
	//printf("\n%dx %dy\n", x, y);
	if (flood_fill(param->map, x, y))
		return (ERROR);
	return (OK);
}
