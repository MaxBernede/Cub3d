/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/26 12:27:02 by maxb          #+#    #+#                 */
/*   Updated: 2023/12/04 17:54:01 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int full_textures(t_param *p)
{
	if (!p->south || !p->north || !p->east || !p->west)
		return (ERROR);
	if (p->floor.r < 0 || p->floor.g < 0 || p->floor.b < 0)
		return (ERROR);
	if (p->ceiling.r < 0 || p->ceiling.g < 0 || p->ceiling.b < 0)
		return (ERROR);
	return (OK);
}

char	*read_new_line(char *sub, t_param *p)
{
	char	*line;

	free(sub);
	line = get_next_line(p->fd);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		sub = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		sub = ft_substr(line, 0, ft_strlen(line));
	if (!sub)
		return (NULL);
	if (!sub[0])
		return (free(sub), free(line), NULL);
	free(line);
	return (sub);
}

int	fill_map(char *sub, t_param *p)
{
	t_map	*map;

	map = &p->map;
	if (sub && map->length < 0)
		map->length = ft_strlen(sub);
	while (sub)
	{
		if (ft_strlen(sub) != map->length || insert_node(&p->tmp_map, sub))
			return (ft_free_lst(p->tmp_map), free(sub), ERROR);
		sub = read_new_line(sub, p);
	}
	p->map.map = get_map(p);
	if (!p->map.map)
		return (ERROR);
	// prepare the floodfill map
	p->map.flood = get_map(p);
	if (!p->map.flood)
		return (ERROR);
	ft_free_lst(p->tmp_map);
	p->tmp_map = NULL;
	// ft_2d_print(p->map.map);
	p->map.height = ft_2d_arrlen(p->map.map);
	p->end_map_parse = true;
	return (OK);
}

int	parse_map(char *line, t_param *p)
{
	char	**split;
	char	*sub;

	if (get_str_without_nl(line, &sub))
		return (OK);
	split = ft_split(sub, ' ');
	if (!split)
		return (free(line), free(sub), ERROR);
	//below line means : if arrlen == 1 means it will start parsing the map, but before i check
	//if there is textures for all the walls otherwise no need to parse
	if (ft_2d_arrlen(split) == 1 && (full_textures(p) || fill_map(sub, p)))
		return (ft_2dfree(split), ERROR);
	ft_2dfree(split);
	// Check below means the map have been filled,so we can check the validity of the map
	if (p->map.map)
		return (check_map(p));
	return (OK);
}
