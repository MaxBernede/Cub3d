#include "cub3d.h"

int	floor_ceiling(int type, char *arg, t_param *p)
{
	if (type == FLOOR && is_colors(arg, &p->floor.r, &p->floor.g, &p->floor.b))
		return (printf(ERR_FILL_COLORS), ERROR);
	if (type == CEILING && is_colors(arg, &p->ceiling.r, &p->ceiling.g,
			&p->ceiling.b))
		return (printf(ERR_FILL_COLORS), ERROR);
	return (OK);
}

int	fill_texture(mlx_texture_t **texture, char *s)
{
	*texture = mlx_load_png(s);
	if (!(*texture))
		return (ERROR);
	return (OK);
}
