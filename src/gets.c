#include "cub3d.h"

// The map is transformed from a linked list to a char **
char	**get_map(t_param *p)
{
	t_node *current;
	char **map;
	int i;

	current = p->tmp_map;
	i = 0;
	map = (char **)malloc((ft_our_lst_size(current) + 1) * sizeof(char *));
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

int get_type(char *line)
{
	if (!ft_strncmp("F ", line, 2))
		return (FLOOR);
	if (!ft_strncmp("C ", line, 2))
		return (CEILING);
	if (!ft_strncmp("NO ", line, 3))
		return (NORTH);
	if (!ft_strncmp("SO ", line, 3))
		return (SOUTH);
	if (!ft_strncmp("EA ", line, 3))
		return (EAST);
	if (!ft_strncmp("WE ", line, 3))
		return (WEST);
	return (ERROR);
}

int	get_char_start(t_map map, int *y, int *x)
{
	*y = 0;
	while (*y < map.height)
	{
		*x = 0;
		while (*x < map.length)
		{
			if (ft_strchr("NSEW", map.map[*y][*x]))
				return (OK);
			++(*x);
		}
		++(*y);
	}
	return (ERROR);
}
