/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_overflow.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/25 20:07:46 by maxb          #+#    #+#                 */
/*   Updated: 2023/11/25 20:07:47 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <limits.h>

void	define_var(int *i, int *sign, int *numb)
{
	*i = 0;
	*sign = 1;
	*numb = 0;
}

int	ft_atoi_overflow(const char *str, int *numb)
{
	int	i;
	int	sign;

	define_var(&i, &sign, numb);
	if (!str)
		return (1);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*numb += str[i] - '0';
		if (*numb < 0 && (*numb != INT_MIN || sign == 1))
			return (1);
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			*numb *= 10;
		i++;
	}
	*numb *= sign;
	return (0);
}
