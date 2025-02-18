/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                             :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:19:33 by rtorrent          #+#    #+#             */
/*   Updated: 2025/02/18 15:29:33 by rtorrent       ########   odam.nl        */
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

char	*ft_getnextline_fd(int fd);
int     ft_snprintf(char *str, size_t size, const char *format, ...);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);

#endif
