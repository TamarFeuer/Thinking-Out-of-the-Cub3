#ifndef LIBFT_H
# define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


void	ft_free_2d(void ***arr);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
int 	ft_atoi_b16(const char *nptr);
int		ft_isdigit(char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char const *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif