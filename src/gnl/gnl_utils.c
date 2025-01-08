#include "../../inc/gnl.h"
#include "../../inc/game.h"

ssize_t	ft_checknl(char *str)
{
	ssize_t	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	*gnl_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
