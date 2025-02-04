#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	ret_value;
	char	*src_ptr;

	ret_value = ft_strlen(src);
	src_ptr = (char *)src;
	if (size == 0)
		return (ret_value);
	while (*src_ptr && (size - 1) > 0)
	{
		*dst = *src_ptr;
		dst++;
		src_ptr++;
		size--;
	}
	*dst = '\0';
	return (ret_value);
}
