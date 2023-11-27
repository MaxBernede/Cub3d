/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:00:12 by maxb          #+#    #+#                 */
/*   Updated: 2023/11/27 17:16:06 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_str_without_nl(char *line, char **sub)
{
	if (!line || !cmp(line, "\n"))
		return (ERROR);
	*sub = ft_substr(line, 0, ft_strlen(line)-1);
	if (!*sub)
		return (ERROR);
	if (!*sub[0])
		return (free(*sub), ERROR);
	return (OK);
}