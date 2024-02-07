/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 15:30:48 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 15:32:48 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_delta(t_player *player, t_vec2 *offset)
{
	if (player->delta.x < 0)
		offset->x = -1;
	else
		offset->x = 1;
	if (player->delta.y < 0)
		offset->y = -1;
	else
		offset->y = 1;
}

void	move_player(t_player *player, char **map, int direction, double dt)
{
	t_vec2	new_pos;
	t_vec2	offset;
	int		mapo;

	if (dt > .25)
		dt = .25;
	fill_delta(player, &offset);
	new_pos.x = player->pos.x + player->delta.x * direction * dt;
	new_pos.y = player->pos.y + player->delta.y * direction * dt;
	mapo = (new_pos.x + offset.x * direction) / TILE_SIZE;
	if (ft_strchr("0NSEW", map[(int)((player->pos.y + 1) / TILE_SIZE)][mapo])
		&& ft_strchr("0NSEW", map[(int)((player->pos.y - 1)
				/ TILE_SIZE)][mapo]))
		player->pos.x = new_pos.x;
	mapo = (new_pos.y + offset.y * direction) / TILE_SIZE;
	if (ft_strchr("0NSEW", map[mapo][(int)((player->pos.x + 1) / TILE_SIZE)])
		&& ft_strchr("0NSEW", map[mapo][(int)((player->pos.x - 1)
				/ TILE_SIZE)]))
		player->pos.y = new_pos.y;
}

void	change_player_angle(t_player *player, int direction, double dt)
{
	player->angle += TURNSPEED * direction * dt;
	if (player->angle < 0)
		player->angle += TWO_PI;
	else if (player->angle > TWO_PI)
		player->angle -= TWO_PI;
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
		player->angle = PI + HALF_PI;
	else
		player->angle = 0;
	player->pos.x = x * TILE_SIZE + TILE_SIZE * 0.5;
	player->pos.y = y * TILE_SIZE + TILE_SIZE * 0.5;
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
}
