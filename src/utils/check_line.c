/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:00:12 by maxb          #+#    #+#                 */
/*   Updated: 2023/12/04 17:51:48 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_str_without_nl(char *line, char **sub)
{
	if (!line || !cmp(line, "\n"))
		return (ERROR);
	*sub = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!*sub)
		return (ERROR);
	if (!*sub[0])
		return (free(*sub), ERROR);
	return (OK);
}

char  *get_str_no_space(char *line)
{
	char **split;
	char *tmp;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	tmp = concatenateStrings(&split[1], ft_2d_arrlen(split) - 1);
	if (!tmp)
		return (ft_2dfree(split), printf(ERR_MLC), NULL);
	ft_2dfree(split);
	free(line);
	return (tmp);
}
