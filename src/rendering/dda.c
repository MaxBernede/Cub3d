/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/16 01:45:30 by bjacobs       #+#    #+#                 */
/*   Updated: 2024/02/07 18:34:47 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

//angle < PI is looking up
// else looking down
int	init_xray(t_ray *ray, t_vec2 origin, float angle)
{
	float	atan;

	if (angle == 0 || angle == PI)
		return (ray->length = 10000, EXIT_FAILURE);
	atan = 1 / tan(angle);
	ray->origin = origin;
	if (angle < PI)
	{
		ray->hit.y = (((int)ray->origin.y >> 3) << 3) - 0.0001;
		ray->ray_step.y = -TILE_SIZE;
	}
	else
	{
		ray->hit.y = (((int)ray->origin.y >> 3) << 3) + TILE_SIZE;
		ray->ray_step.y = TILE_SIZE;
	}
	ray->hit.x = (ray->hit.y - ray->origin.y) * atan + ray->origin.x;
	ray->ray_step.x = ray->ray_step.y * atan;
	if (ray->ray_step.y == TILE_SIZE)
		ray->side = S_SOUTH;
	else
		ray->side = S_NORTH;
	return (EXIT_SUCCESS);
}

// angle < HALF_PI || angle > THIRD_PI is looking left
// else right
int	init_yray(t_ray *ray, t_vec2 origin, float angle)
{
	float	atan;

	if (angle == HALF_PI || angle == THIRD_PI)
		return (ray->length = 10000, EXIT_FAILURE);
	atan = tan(angle);
	ray->origin = origin;
	if (angle < HALF_PI || angle > THIRD_PI)
	{
		ray->hit.x = (((int)ray->origin.x >> 3) << 3) - 0.0001;
		ray->ray_step.x = -TILE_SIZE;
		ray->side = S_WEST;
	}
	else
	{
		ray->hit.x = (((int)ray->origin.x >> 3) << 3) + TILE_SIZE;
		ray->ray_step.x = TILE_SIZE;
		ray->side = S_EAST;
	}
	ray->hit.y = (ray->hit.x - ray->origin.x) * atan + ray->origin.y;
	ray->ray_step.y = ray->ray_step.x * atan;
	return (EXIT_SUCCESS);
}

void	cast_ray(t_ray *ray, t_map map)
{
	int	mapx;
	int	mapy;

	mapx = (int)ray->hit.x >> 3;
	mapy = (int)ray->hit.y >> 3;
	while (mapy < map.height && mapx < map.length && mapy >= 0 && mapx >= 0
		&& map.map[mapy][mapx] != '1')
	{
		ray->hit.y += ray->ray_step.y;
		ray->hit.x += ray->ray_step.x;
		mapx = (int)ray->hit.x >> 3;
		mapy = (int)ray->hit.y >> 3;
	}
	ray->length = sqrt((ray->origin.x - ray->hit.x) * (ray->origin.x
				- ray->hit.x) + (ray->origin.y - ray->hit.y) * (ray->origin.y
				- ray->hit.y));
}

void	init_dda(t_dda *data, float player_angle)
{
	data->angle = player_angle - (ONE_DEGREE * FOV) / 2;
	if (data->angle < 0)
		data->angle += TWO_PI;
	data->rays = 0;
}

void	dda(t_dda *data, t_vec2 player_pos, t_map map)
{
	if (!init_xray(&data->xray, player_pos, data->angle))
		cast_ray(&data->xray, map);
	if (!init_yray(&data->yray, player_pos, data->angle))
		cast_ray(&data->yray, map);
	if (data->xray.length < data->yray.length)
		data->hit_ray = data->xray;
	else
		data->hit_ray = data->yray;
}
