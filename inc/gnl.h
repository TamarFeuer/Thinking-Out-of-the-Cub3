#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* GNL */
char	*get_next_line(int fd);
char	*ft_parse(char **rem);
char	*ft_get_new_rem(char *rem);
char	*ft_get_nl_line(char *rem);
void	ft_read(int fd, char **rem);

/* UTILS */
ssize_t	ft_checknl(char *str);
void	*gnl_free(char **str);

#endif