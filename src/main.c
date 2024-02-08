/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:17 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/08 17:51:33 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this is made to free more easily in case of a parsing error
void	init_null(t_param *p)
{
	int	i;

	i = 0;
	while (i < 4)
		p->textures[i++] = NULL;
	p->ceiling.r = -1;
	p->ceiling.g = -1;
	p->ceiling.b = -1;
	p->floor.r = -1;
	p->floor.g = -1;
	p->floor.b = -1;
	p->shapes = NULL;
	p->end_map_parse = false;
	p->map.length = -1;
	p->map.height = 0;
	p->map.map = NULL;
	p->map.flood = NULL;
	p->tmp_map = NULL;
	p->window.height = 512;
	p->window.width = 1024;
	p->door_key[0] = NULL;
	p->door_key[1] = NULL;
}

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2)
		return (printf(ERR_ARG), 1);
	init_null(&param);
	if (check_file(argv[1]))
		return (1);
	if (parse_file(argv[1], &param))
		return (1);
	if (!search_in_map(&param, "D") && !param.door_key[0])
		return (printf(ERR_NOTEXT), 1);
	if (!search_in_map(&param, "K") && !param.door_key[1])
		return (printf(ERR_NOTEXT), 1);
	if (start(&param, param.window))
		return (0);
	clean_everything(&param);
	return (0);
}
