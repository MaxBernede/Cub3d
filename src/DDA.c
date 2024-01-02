/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:45:30 by bjacobs           #+#    #+#             */
/*   Updated: 2024/01/01 23:11:31 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int	init_xray(t_ray *ray, t_vec2 origin, float angle)
{
	float	atan;

	if (angle == 0 || angle == PI)
		return (ray->length = 10000, EXIT_FAILURE);
	atan = 1 / tan(angle);
	ray->origin = origin;
	if (angle < PI) // looking up
	{
		ray->hit.y = (((int)ray->origin.y >> 4) << 4) - 0.0001;
		ray->ray_step.y = -TILE_SIZE;
	}
	else // otherwise looking down
	{
		ray->hit.y = (((int)ray->origin.y >> 4) << 4) + TILE_SIZE;
		ray->ray_step.y = TILE_SIZE;
	}
	ray->hit.x = (ray->hit.y - ray->origin.y) * atan + ray->origin.x;
	ray->ray_step.x = ray->ray_step.y * atan;
	return (EXIT_SUCCESS);
}

int	init_yray(t_ray *ray, t_vec2 origin, float angle)
{
	float	atan;

	if (angle == HALF_PI || angle == THIRD_PI)
		return (ray->length = 10000, EXIT_FAILURE);
	atan = tan(angle);
	ray->origin = origin;
	if (angle < HALF_PI  ||  angle > THIRD_PI) // looking left
	{
		ray->hit.x = (((int)ray->origin.x >> 4) << 4) - 0.0001;
		ray->ray_step.x = -TILE_SIZE;
	}
	else // otherwise looking right
	{
		ray->hit.x = (((int)ray->origin.x >> 4) << 4) + TILE_SIZE;
		ray->ray_step.x = TILE_SIZE;
	}
	ray->hit.y = (ray->hit.x - ray->origin.x) * atan + ray->origin.y;
	ray->ray_step.y = ray->ray_step.x * atan;
	return (EXIT_SUCCESS);
}

void	cast_ray(t_ray *ray, t_map map)
{
	int	mapx;
	int	mapy;

	mapx = (int)ray->hit.x >> 4;
	mapy = (int)ray->hit.y >> 4;
	while (mapy < map.height && mapx < map.length && mapy >= 0 && mapx >= 0 && map.map[mapy][mapx] != '1')
	{
		ray->hit.y += ray->ray_step.y;
		ray->hit.x += ray->ray_step.x;
		mapx = (int)ray->hit.x >> 4;
		mapy = (int)ray->hit.y >> 4;
	}
	ray->length = sqrt((ray->origin.x - ray->hit.x) * (ray->origin.x - ray->hit.x)
					+ (ray->origin.y - ray->hit.y) * (ray->origin.y - ray->hit.y));
	//printf("length: %f\n", ray->length);
}

void	DDA(t_player player, t_map map)
{
	t_dda	data;

	data.angle = player.angle - (ONE_DEGREE * FOV) / 2;
	if (data.angle < 0)
		data.angle += TWO_PI;
	data.rays = 0;
	while (data.rays < FOV)
	{
		if (!init_xray(&data.xray, player.pos, data.angle))
			cast_ray(&data.xray, map);
		if (!init_yray(&data.yray, player.pos, data.angle))
			cast_ray(&data.yray, map);
		if (data.xray.length < data.yray.length)
			data.hit = data.xray.hit;
		else
			data.hit = data.yray.hit;
		data.angle += ONE_DEGREE;
		if (data.angle > TWO_PI)
			data.angle -= TWO_PI;
		//printf("close hit: x %f,  y %f\n", hit.x, hit.y);
		draw_line(map.minimap, data.hit, player.pos, 0xFFFF00FF);
		data.rays++;
	}
}
