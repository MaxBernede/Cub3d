#include "cub3d.h"

//check in case of a format rgb like : 255,240,0
int nb_or_comma(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ',')
			return (ERROR);
		i++;
	}
	return (OK);
}
