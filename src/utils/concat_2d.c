/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernede <mbernede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:28:08 by mbernede          #+#    #+#             */
/*   Updated: 2024/02/07 13:28:09 by mbernede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*concatenate_strings(char **strings, int num_string)
{
	int		total_len;
	char	*result;
	int		index;
	int		i;

	total_len = 0;
	i = -1;
	while (++i < num_string)
		total_len += ft_strlen(strings[i]);
	result = (char *)malloc(total_len + 1);
	if (!result)
		return (printf(ERR_MLC), NULL);
	index = 0;
	i = -1;
	while (++i < num_string)
		index += ft_strlcpy(result + index, strings[i], total_len + 1
				- index);
	return (result);
}
