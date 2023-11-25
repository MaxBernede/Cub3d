#include "cub3d.h"

int floor_ceiling(char **split, t_param *p)
{
	if (ft_2d_arrlen(split) != 2 || cmp(split[0], "F") || cmp(split[0], "C"))
		return (printf(ERR_FLOOR_CEILING), ERROR);
	if (!cmp(split[0], "F") && is_colors(split[1], &p->floor.r, &p->floor.g, &p->floor.b))
		return (printf(ERR_FILL_COLORS),ERROR);
	else if (!cmp(split[0], "C") && is_colors(split[1], &p->ceiling.r, &p->ceiling.g, &p->ceiling.b))
		return (printf(ERR_FILL_COLORS),ERROR);
	return (OK);
}

int side_textures(char **split, t_param *param)
{
	if (ft_2d_arrlen(split) != 2 || cmp(split[0], "NO") || cmp(split[0], "SO")|| cmp(split[0], "EA")|| cmp(split[0], "WE"))
		return (printf(ERR_TEXTURES), ERROR);
	
	if (type == 'r' && fill_window(split, param))
		return (printf(ERR_WINDOW), ERROR);
	else if (type != 'c' && type != 'a' && type != 'l' && type != 'r')
		return (printf(ERR_ADD_PARAM), ERROR);
	return (OK);
}

//check if needed to split based on isspace
int check_line(char *line, t_param *param)
{
	char **split;
	char *sub;

	if (!line || !cmp(line, "\n"))
		return (OK);
	//remove the '\n'
	sub = ft_substr(line, 0, ft_strlen(line)-1);
	if (!sub || !sub[0])
		return (OK);
	split = ft_split(sub, ' ');
	free(sub);
	if (ft_strlen(split[0]) == 1 && floor_ceiling(split, param))
			return (ft_2dfree(split), ERROR);
	else if (ft_strlen(split[0]) == 2 && side_textures(split, param))
			return (ft_2dfree(split), ERROR);
	ft_2dfree(split);
	return (OK);
}

int fill_datas(char *arg, t_param *param)
{
	int fd;
	char *line;

	fd = open_file(arg);
	if (fd <= 0)
		return (ERROR);
	line = get_next_line(fd);
	while (line)
	{
		if (check_line(line, param))
			return (free(line), printf(ERR_FILE_DATA), close(fd), ERROR);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (OK);
}
