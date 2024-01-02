#include "cub3d.h"

char* concatenateStrings(char** strings, int numStrings) {
    int		totalLength;
	char	*result;
	int		index;
	int		i;

	totalLength = 0;
    for (i = 0; i < numStrings; i++)
        totalLength += ft_strlen(strings[i]);
    result = (char*)malloc(totalLength + 1);
    if (!result)
        return (printf(ERR_MLC), NULL);
    index = 0;
    for (i = 0; i < numStrings; i++)
        index += ft_strlcpy(result + index, strings[i], totalLength + 1 - index);
    return result;
}