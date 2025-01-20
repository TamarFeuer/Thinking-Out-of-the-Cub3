#include "../../inc/gnl.h"
#include "../../inc/game.h"

bool	ft_hasnl(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (false);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
			return (true);
	}
	return (false);
}








































// ssize_t	ft_checknl(char *str)
// {
// 	ssize_t	i;

// 	if (str == NULL)
// 		return (-1);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\n')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// void	*gnl_free(char **str)
// {
// 	if (*str)
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// 	return (NULL);
// }
