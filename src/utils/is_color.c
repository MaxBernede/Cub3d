#include "cub3d.h"

//fill the colors could be changed with structure to be more easy to read
int	is_colors(char *s, int *r, int *g, int *b)
{
	char **split;

	if (ft_strlen(s) > 11 || nb_or_comma(s))
		return (ERROR);
	split = ft_split(s, ',');
	if (!split)
		return (ERROR);
	if (ft_2d_arrlen(split) != 3)
		return (ft_2dfree(split), ERROR);
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	if (*r > 255 || *g > 255 || *b > 255)
		return (ft_2dfree(split), ERROR);
	return (ft_2dfree(split),OK);
}
