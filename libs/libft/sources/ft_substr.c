#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		start = s_len;
		len = 0;
	}
	if (len + start > s_len)
		len = s_len - start;
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
