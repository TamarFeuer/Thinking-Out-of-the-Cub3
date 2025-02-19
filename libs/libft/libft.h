/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                             :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:19:33 by rtorrent          #+#    #+#             */
/*   Updated: 2025/02/19 16:53:29 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

// external declarations from the libc (AKA 'authorized functions')
void	free(void *ptr);
void	*malloc(size_t size);
ssize_t	read(int fildes, void *buf, size_t nbyte);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// buffer size for read operations
// (=BUFSIZ constant defined in stdio.h)
// used in: ft_getnextline_fd
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// by default, maximum number of files that Mac OS X can open
// used in: ft_getnextline_fd
# ifndef MAX_FILES
#  define MAX_FILES 12288
# endif

// minimim list size and subsequent batch allocations
// used in: ft_getnextline_fd
# ifndef DEFAULT_BATCH_SZE
#  define DEFAULT_BATCH_SZE 10
# endif

/* ************************************************************************** */

char	*ft_getnextline_fd(char **line, int fd);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_snprintf(char *str, size_t size, const char *format, ...);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strcspn(const char *s, const char *reject);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strspn(const char *s, const char *accept);
char	*ft_strtok(char *s, const char *delim);
char	*ft_strtok_r(char *s, const char *delim, char **saveptr);
char	*ft_substr(const char *s, size_t start, size_t len);

/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

void	ft_lstadd_back(t_list **plst, t_list *new);
void	ft_lstclear(t_list **plst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);

#endif
