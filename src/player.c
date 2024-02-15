/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 15:30:48 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/15 20:45:00 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec2	init_movement(t_player *player, int *offset,
	bool strafing, double direction)
{
	t_vec2	new_pos;
	t_vec2	delta;

	if (strafing)
		delta = v2_new(-player->delta.y, player->delta.x);
	else
		delta = player->delta;
	if (delta.x < 0)
		offset[X] = -1;
	else
		offset[X] = 1;
	if (delta.y < 0)
		offset[Y] = -1;
	else
		offset[Y] = 1;
	new_pos.x = player->pos.x + delta.x * direction;
	new_pos.y = player->pos.y + delta.y * direction;
	return (new_pos);
}

void	move_player(t_param *p, bool strafing, int direction, double dt)
{
	t_vec2	new_pos;
	int		offset[2];
	int		mapo[2];

	if (dt > .25)
		dt = .25;
	new_pos = init_movement(&p->player, offset, strafing, direction * dt);
	mapo[X] = (new_pos.x + offset[X] * direction) / CELL_SIZE;
	mapo[Y] = (int)(p->player.pos.y + 1) / CELL_SIZE;
	if (!ft_strchr("1D", p->map.map[mapo[Y]][mapo[X]])
		&& !ft_strchr("1D", p->map.map[mapo[Y]][mapo[X]]))
	{
		p->player.pos.x = new_pos.x;
	}
	mapo[X] = (int)(p->player.pos.x + 1) / CELL_SIZE;
	mapo[Y] = (new_pos.y + offset[Y] * direction) / CELL_SIZE;
	if (!ft_strchr("1D", p->map.map[mapo[Y]][mapo[X]])
		&& !ft_strchr("1D", p->map.map[mapo[Y]][mapo[X]]))
	{
		p->player.pos.y = new_pos.y;
	}
}

void	open_door(t_player *player, t_map *map)
{
	t_dda	data;

	data.angle = player->angle;
	dda(&data, player, *map, 1);
	if (data.ray.side == S_DOOR && data.ray.length <= 10)
		map->map[(int)data.ray.hit.y >> 3][(int)data.ray.hit.x >> 3] = '0';
}

void	change_player_angle(t_player *player, double turnspeed, double dt)
{
	player->angle = fix_angle(player->angle + turnspeed * dt);
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
}

void	init_player(t_map map, t_player *player)
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
	player->pos.x = x * CELL_SIZE + CELL_SIZE * 0.5;
	player->pos.y = y * CELL_SIZE + CELL_SIZE * 0.5;
	player->delta.x = cos(player->angle) * WALKSPEED;
	player->delta.y = sin(player->angle) * WALKSPEED;
}
