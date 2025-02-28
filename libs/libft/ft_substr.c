/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:43:27 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/04 17:50:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, size_t start, size_t len)
{
	size_t	size;
	char	*p;

	size = ft_strlen(s);
	if (start > size)
		return (ft_calloc(1, 1));
	size -= start;
	if (len < size)
		size = len;
	p = malloc(++size);
	if (p)
		ft_strlcpy(p, s + start, size);
	return (p);
}
