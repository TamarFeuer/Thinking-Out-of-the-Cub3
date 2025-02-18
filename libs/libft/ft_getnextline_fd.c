/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline_fd.c                                 :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2025/02/18 19:30:47 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_getnextline_fd.h"

static void	clear_blocks(t_blocks *plist, bool skip_first)
{
	t_blocks	prev;

	while (*plist)
	{
		prev = (*plist)->prev;
		if (!(*plist)->index || !prev)
		{
			if (!skip_first)
				free(*plist - (*plist)->index);
			else
				skip_first = false;
		}
		*plist = prev;
	}
}

static bool	asm_line(t_blocks *plst_copy, t_blocks *plst_del, char **line)
{
	size_t		size;
	t_blocks	blocks;

	size = 0;
	blocks = *plst_copy;
	while (blocks)
	{
		size += blocks->len;
		blocks = blocks->prev;
	}
	if (size)
		*line = malloc(size + 1);
	if (*line)
	{
		*line += size;
		**line = '\0';
		blocks = *plst_copy;
		while (blocks)
		{
			*line = ft_memcpy(*line - blocks->len, blocks->start, blocks->len);
			blocks = blocks->prev;
		}
		clear_blocks(plst_del, *plst_copy != *plst_del && (*plst_copy)->index);
	}
	return (*line);
}

static ssize_t	add_block(int fd, t_blocks *plist)
{
	const bool	new_batch = !*plist || (*plist)->index == DEFAULT_BATCH_SZE - 1;
	t_blocks	new_block;
	ssize_t		n;

	if (new_batch)
		new_block = malloc(sizeof(struct s_block) * DEFAULT_BATCH_SZE);
	else
		new_block = (*plist) + 1;
	if (!new_block)
		return (-1);
	n = read(fd, new_block->str, BUFFER_SIZE);
	if (n > 0)
	{
		new_block->len = n;
		if (new_batch)
			new_block->index = 0;
		else
			new_block->index = (*plist)->index + 1;
		new_block->prev = *plist;
		new_block->start = new_block->str;
		*plist = new_block;
	}
	else if (new_batch)
		free(new_block);
	return (n);
}

static bool	read_blocks(int fd, t_blocks *plist, char **line)
{
	char	*p_nl;
	ssize_t	n;

	p_nl = NULL;
	if (*plist)
		p_nl = ft_memchr((*plist)->start, '\n', (*plist)->len);
	while (!p_nl)
	{
		n = add_block(fd, plist);
		if (n < 0)
			return (false);
		if (n == 0)
			return (asm_line(plist, plist, line));
		p_nl = ft_memchr((*plist)->start, '\n', (*plist)->len);
	}
	n = (*plist)->len;
	(*plist)->len = ++p_nl - (*plist)->start;
	if (!asm_line(plist, &(*plist)->prev, line))
		return (false);
	(*plist)->len = n - (*plist)->len;
	(*plist)->start = p_nl;
	return ((*plist)->len);
}

char	*ft_getnextline_fd(char **line, int fd)
{
	static t_blocks	listed_lines[MAX_FILES];

	if (fd < 0 || fd >= MAX_FILES || BUFFER_SIZE <= 0 || DEFAULT_BATCH_SZE <= 0)
		return (NULL);
	if (!line)
	{
		clear_blocks(&listed_lines[fd], false);
		return (NULL);
	}
	*line = NULL;
	if (!read_blocks(fd, &listed_lines[fd], line))
		clear_blocks(&listed_lines[fd], false);
	return (*line);
}
