#include "cub3d.h"

// this is made to free more easily in case of a parsing error
void	init_null(t_param *p)
{
	p->east = NULL;
	p->north = NULL;
	p->south = NULL;
	p->west = NULL;
	p->shapes = NULL;
	p->end_map_parse = false;
	p->map.length = -1;
	p->map.height = 0;
	p->map.map = NULL;
	p->map.flood = NULL;
	p->tmp_map = NULL;
	p->window.height = 1024;
	p->window.width = 1024;
}

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2)
		return (printf(ERR_ARG), 1);
	init_null(&param);
	if (check_file(argv[1]))
		return (1);
	if (fill_datas(argv[1], &param))
		return (1);
	if (start(&param, param.window))
		return (0);
	clean_everything(&param);
	return (0);
}
