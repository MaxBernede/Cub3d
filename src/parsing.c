#include "cub3d.h"

// Check the textures exists and can be opened them assigned them to the structure
int	side_textures(int type, char *arg, t_param *p)
{
	int	fd;

	fd = open_file(arg);
	if (fd < 1)
		return (printf(ERR_OPEN_TEXTURES), ERROR);
	close(fd);
	if (type == NORTH && fill_texture(&(p->north), arg))
		return (printf(ERR_NO), ERROR);
	if (type == SOUTH && fill_texture(&(p->south), arg))
		return (printf(ERR_SO), ERROR);
	if (type == EAST && fill_texture(&(p->east), arg))
		return (printf(ERR_EA), ERROR);
	if (type == WEST && fill_texture(&(p->west), arg))
		return (printf(ERR_WE), ERROR);
	return (OK);
}

//remove the \n then check if empty
//next, make a string with the rest of the output then fill
int	check_line(char *line, t_param *param)
{
	char	*sub;
	int		type;

	if (get_str_without_nl(line, &sub))
		return (OK);
	type = get_type(sub);
	if (type == ERROR)
		return (printf(ERR_TYPE), ERROR);
	sub = get_str_no_space(sub);
	if (!sub)
		return (printf(ERR_MLC), ERROR);
	if ((type == FLOOR || type == CEILING) && floor_ceiling(type, sub, param))
		return (free(sub), ERROR);
	else if (type >= NORTH && side_textures(type, sub, param))
		return (free(sub), ERROR);
	free(sub);
	return (OK);
}

// will check the if we need to fill map, in case it start filling the map
// the program won't run the checkline after parsemap itself will check
// that there is nothing after the parsing of the map and we reached the end of the file or at least only \n
int	parse_file(char *arg, t_param *p)
{
	char	*line;

	p->fd = open_file(arg);
	if (p->fd <= 0)
		return (ERROR);
	line = get_next_line(p->fd);
	if (!line)
		return (printf(ERR_EMPTY_MAP), ERROR);
	while (line)
	{
		if (parse_map(line, p))
			return (printf(ERR_FILL_MAP), close(p->fd), ERROR);
		if (!p->end_map_parse && check_line(line, p))
			return (free(line), printf(ERR_FILE_DATA), close(p->fd), ERROR);
		free(line);
		line = get_next_line(p->fd);
	}
	close(p->fd);
	if (!p->map.map)
		return (printf(ERR_NO_MAP), ERROR);
	return (OK);
}
