#include "cub3d.h"

int	floor_ceiling(char **split, t_param *p)
{
	if (ft_2d_arrlen(split) != 2 || (!cmp(split[0], "F") && !cmp(split[0],
				"C")))
		return (printf(ERR_FLOOR_CEILING), ERROR);
	if (!cmp(split[0], "F") && is_colors(split[1], &p->floor.r, &p->floor.g,
			&p->floor.b))
		return (printf(ERR_FILL_COLORS), ERROR);
	else if (!cmp(split[0], "C") && is_colors(split[1], &p->ceiling.r,
			&p->ceiling.g, &p->ceiling.b))
		return (printf(ERR_FILL_COLORS), ERROR);
	return (OK);
}

int	fill_texture(mlx_texture_t *texture, char *s)
{
	texture = mlx_load_png(s);
	if (!texture)
		return (ERROR);
	return (OK);
}

// Check the textures exists and can be opened them assigned them to the structure
int	side_textures(char **split, t_param *p)
{
	int	fd;

	if (ft_2d_arrlen(split) != 2 || (cmp(split[0], "NO") && cmp(split[0], "SO")
			&& cmp(split[0], "EA") && cmp(split[0], "WE")))
		return (printf(ERR_TEXTURES), ERROR);
	fd = open_file(split[1]);
	if (fd < 1)
		return (printf(ERR_OPEN_TEXTURES), ERROR);
	close(fd);
	if (!cmp(split[0], "NO") && fill_texture(p->north, split[1]))
		return (printf(ERR_NO), ERROR);
	if (!cmp(split[0], "SO") && fill_texture(p->south, split[1]))
		return (printf(ERR_SO), ERROR);
	if (!cmp(split[0], "EA") && fill_texture(p->east, split[1]))
		return (printf(ERR_EA), ERROR);
	if (!cmp(split[0], "WE") && fill_texture(p->west, split[1]))
		return (printf(ERR_WE), ERROR);
	return (OK);
}

// check if needed to split based on isspace
int	check_line(char *line, t_param *param)
{
	char	**split;
	char	*sub;

	if (get_str_without_nl(line, &sub))
		return (OK);
	split = ft_split(sub, ' ');
	if (!split)
		return (free(sub), ERROR);
	free(sub);
	if (ft_strlen(split[0]) == 1 && floor_ceiling(split, param))
		return (ft_2dfree(split), ERROR);
	else if (ft_strlen(split[0]) == 2 && side_textures(split, param))
		return (ft_2dfree(split), ERROR);
	ft_2dfree(split);
	return (OK);
}

// will check the if we need to fill map, in case it start filling the map
// the program won't run the checkline after parsemap itself will check
// that there is nothing after the parsing of the map and we reached the end of the file or at least only \n
int	fill_datas(char *arg, t_param *p)
{
	char	*line;

	p->fd = open_file(arg);
	if (p->fd <= 0)
		return (ERROR);
	line = get_next_line(p->fd);
	while (line)
	{
		//! line not free anymore here for parse map and should be free
		// printf("data :%s %d\n", line, p->end_map_parse);
		if (parse_map(line, p))
			return (printf(ERR_FILL_MAP), close(p->fd), ERROR);
		if (!p->end_map_parse && check_line(line, p))
			return (free(line), printf(ERR_FILE_DATA), close(p->fd), ERROR);
		free(line);
		line = get_next_line(p->fd);
	}
	close(p->fd);
	return (OK);
}
