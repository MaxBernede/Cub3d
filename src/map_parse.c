/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/26 12:27:02 by maxb          #+#    #+#                 */
/*   Updated: 2023/11/27 20:09:24 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *read_new_line(char *sub, t_param *p)
{
	char *line;

	free(sub);
	line = get_next_line(p->fd);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		sub = ft_substr(line, 0, ft_strlen(line)-1);
	else
		sub = ft_substr(line, 0, ft_strlen(line));
	if (!sub)
		return (NULL);
	if (!sub[0])
		return (free(sub), free(line), NULL);
	free(line);
	return sub;
}

int fill_map(char *sub, t_param *p)
{
	t_map *map;

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
	ft_2d_print(p->map.map);
	p->map.height = ft_2d_arrlen(p->map.map);
	p->end_map_parse = true;
	return (OK);
}

int parse_map(char *line, t_param *param)
{
	char **split;
	char *sub;

	if (get_str_without_nl(line, &sub))
		return (OK);
	split = ft_split(sub, ' ');
	if (!split)
		return (free(line), free(sub), ERROR);
	if (ft_2d_arrlen(split) == 1 && fill_map(sub, param))
			return (ft_2dfree(split), ERROR);
	ft_2dfree(split);
	//Check below means the map have been filled, so we can check the validity of the map
	if (param->map.map)
		return (check_map(param));
	return (OK);
}

//The map is transformed from a linked list to a char **
char	**get_map(t_param *p)
{
	t_node	*current;
	char	**map;
	int		i;

	current = p->tmp_map;
	i = 0;
	map = (char **) malloc((ft_our_lst_size(current) + 1) * sizeof(char *));
	if (!map)
		return (printf(ERR_MLC), NULL);
	while (current)
	{
		map[i] = ft_strdup(current->line);
		current = current->next;
		++i;
	}
	map[i] = NULL;
	return (map);
}