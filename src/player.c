/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 15:30:48 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/11 04:02:37 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_offset(double x,  double y, int *offset)
{
	if (x < 0)
		offset[X] = -1;
	else
		offset[X] = 1;
	if (y < 0)
		offset[Y] = -1;
	else
		offset[Y] = 1;
}

void	move_player_y(t_player *player, char **map, int direction, double dt)
{
	t_vec2	new_pos;
	int		offset[2];
	int		mapo;

	if (dt > .25)
		dt = .25;
	init_offset(player->delta.x, player->delta.y, offset);
	new_pos.x = player->pos.x + player->delta.x * direction * dt;
	new_pos.y = player->pos.y + player->delta.y * direction * dt;
	mapo = (new_pos.x + offset[X] * direction) / TILE_SIZE;
	if (!ft_strchr("1D", map[(int)((player->pos.y + 1) / TILE_SIZE)][mapo])
		&& !ft_strchr("1D", map[(int)((player->pos.y - 1)
				/ TILE_SIZE)][mapo]))
		player->pos.x = new_pos.x;
	mapo = (new_pos.y + offset[Y] * direction) / TILE_SIZE;
	if (!ft_strchr("1D", map[mapo][(int)((player->pos.x + 1) / TILE_SIZE)])
		&& !ft_strchr("1D", map[mapo][(int)((player->pos.x - 1)
				/ TILE_SIZE)]))
		player->pos.y = new_pos.y;
}

void	move_player_x(t_player *player, char **map, int direction, double dt)
{
	t_vec2	new_pos;
	int		offset[2];
	int		mapo;

	if (dt > .25)
		dt = .25;
	init_offset(-player->delta.y, player->delta.x, offset);
	new_pos.x = player->pos.x + -player->delta.y * direction * dt;
	new_pos.y = player->pos.y + player->delta.x * direction * dt;
	mapo = (new_pos.x + offset[X] * direction) / TILE_SIZE;
	if (!ft_strchr("1D", map[(int)((player->pos.y + 1) / TILE_SIZE)][mapo])
		&& !ft_strchr("1D", map[(int)((player->pos.y - 1)
				/ TILE_SIZE)][mapo]))
		player->pos.x = new_pos.x;
	mapo = (new_pos.y + offset[Y] * direction) / TILE_SIZE;
	if (!ft_strchr("1D", map[mapo][(int)((player->pos.x + 1) / TILE_SIZE)])
		&& !ft_strchr("1D", map[mapo][(int)((player->pos.x - 1)
				/ TILE_SIZE)]))
		player->pos.y = new_pos.y;
}

void	open_door(t_player *player, t_map *map)
{
	t_dda	data;

	init_dda(&data, player->angle);
	dda(&data, player, *map, 1);
	if (data.ray.side == S_DOOR  && data.ray.length <= 10)
		map->map[(int)data.ray.hit.y >> 3][(int)data.ray.hit.x >> 3] = '0';
}

void	change_player_angle(t_player *player, double turnspeed, double dt)
{
	player->angle += turnspeed * dt;
	player->angle = fix_angle(player->angle);
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
}

void	init_player(t_map map, t_player *player, t_color floor)
{
	char	direction;
	int		x;
	int		y;

	get_char_start(map, &y, &x);
	direction = map.map[y][x];
	printf("player x: %d, player y: %d, direction: %c\n", x, y, direction);
	if (direction == 'N')
		player->angle = HALF_PI;
	else if (direction == 'W')
		player->angle = PI;
	else if (direction == 'S')
		player->angle = THIRD_PI;
	else
		player->angle = 0;
	player->pos.x = x * TILE_SIZE + TILE_SIZE * 0.5;
	player->pos.y = y * TILE_SIZE + TILE_SIZE * 0.5;
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
}
