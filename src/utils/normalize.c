#include "cub3d.h"

int	process_string(char **input, int n) {
    int len ;
    char *result;

	len = ft_strlen(*input);

    if (len == n)
        return (OK);
    result = (char*)malloc((n + 1) * sizeof(char));
	if (len > n)
        ft_strlcpy(result, *input, n + 1);
	else 
	{
        ft_strlcpy(result, *input, len + 1);
        for (int i = len; i < n; ++i)
            result[i] = ' ';
        result[n] = '\0';
    }
	free(*input);
	*input = ft_strdup(result);
	return (OK);
}

void normalize_map(t_param *p)
{
	t_node *tmp;

	tmp = p->tmp_map;
	while (tmp)
	{
		process_string(&(tmp->line), p->map.length);
		//printf("tmp->line: %s\n", tmp->line);
		tmp = tmp->next;
	}
}
