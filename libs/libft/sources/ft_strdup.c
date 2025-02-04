#include "../includes/libft.h"

char	*ft_strdup(char const *str)
{
	char	*new;
	ssize_t	len;
	ssize_t	i;

	len = ft_strlen((char *) str);
	new = malloc (len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str && str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
