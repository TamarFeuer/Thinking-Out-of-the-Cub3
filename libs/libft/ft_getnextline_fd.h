/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline_fd.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/30 19:49:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETNEXTLINE_FD_H
# define FT_GETNEXTLINE_FD_H

// buffer size for read operations
// (=BUFSIZ constant defined in stdio.h)
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// by default, maximum number of files that Mac OS X can open
# ifndef MAX_FILES
#  define MAX_FILES 12288
# endif

// minimim list size and subsequent batch allocations
# ifndef DEFAULT_BATCH_SZE
#  define DEFAULT_BATCH_SZE 10
# endif

typedef struct s_block
{
	size_t			len;
	unsigned int	index;
	struct s_block	*prev;
	char			*start;
	char			str[BUFFER_SIZE];
}	*t_blocks;

#endif
