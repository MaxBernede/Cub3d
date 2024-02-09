/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/16 01:45:30 by bjacobs       #+#    #+#                 */
/*   Updated: 2024/02/09 21:06:58 by bjacobs          ###   ########.fr       */
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
	atan = 1.0 / tan(angle);
	ray->origin = origin;
	ray->type = X;
	if (angle < PI)
	{
		ray->hit.y = (((int)ray->origin.y >> 3) << 3) - 0.0001;
		ray->ray_step.y = -TILE_SIZE;
		ray->side = S_NORTH;
	}
	else
	{
		ray->hit.y = (((int)ray->origin.y >> 3) << 3) + TILE_SIZE;
		ray->ray_step.y = TILE_SIZE;
		ray->side = S_SOUTH;
	}
	ray->hit.x = (ray->hit.y - ray->origin.y) * atan + ray->origin.x;
	ray->ray_step.x = ray->ray_step.y * atan;
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
	ray->type = Y;
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

void	cast_ray(t_ray *ray, t_map map, float player_angle, char *hit_condition)
{
	int	mapx;
	int	mapy;

	mapx = (int)ray->hit.x >> 3;
	mapy = (int)ray->hit.y >> 3;
	while (mapy < map.height && mapx < map.length && mapy >= 0 && mapx >= 0
		&& !ft_strchr(hit_condition, map.map[mapy][mapx]))
	{
		ray->hit.y += ray->ray_step.y;
		ray->hit.x += ray->ray_step.x;
		mapx = (int)ray->hit.x >> 3;
		mapy = (int)ray->hit.y >> 3;
	}
	//if (map.map[mapy][mapx] == 'D') comment out for open_door function to work
	//	ray->side = S_DOOR;
	ray->length = -((ray->hit.x - ray->origin.x) * cos(player_angle) \
			+ (ray->hit.y - ray->origin.y) * sin(player_angle));
}

void	init_dda(t_dda *data, float ray_angle)
{
	data->angle = ray_angle;
	if (data->angle < 0)
		data->angle += TWO_PI;
	data->rays = 0;
}

void	dda(t_dda *data, t_player *player, t_map map, char *hit_condition)
{
	t_ray	ray;

	if (!init_xray(&data->ray, player->pos, data->angle))
		cast_ray(&data->ray, map, player->angle, hit_condition);
	if (!init_yray(&ray, player->pos, data->angle))
		cast_ray(&ray, map, player->angle, hit_condition);
	if (data->ray.length > ray.length)
		data->ray = ray;
}
