#include "cub3d.h"

// makes the number a double
double	ft_atof(char *nptr)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.1;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' && nptr++)
		sign = -1;
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		while (*nptr >= '0' && *nptr <= '9')
		{
			result += (*nptr - '0') * fraction;
			fraction /= 10.0;
			nptr++;
		}
	}
	return (result * sign);
}
