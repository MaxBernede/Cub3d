/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prints.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:18:48 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 13:50:26 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_pos(t_vec3 vec)
{
	printf("(%.2f,%.2f,%.2f) ", vec.x, vec.y, vec.z);
}

void	print_color(t_color color)
{
	printf("colors:(%d,%d,%d) ", color.r, color.g, color.b);
}
