/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:47:12 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/13 00:33:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char *const	src0 = src;

	while (size > 1 && *src)
	{
		*dst++ = *src++;
		size--;
	}
	if (size)
		*dst = '\0';
	while (*src)
		src++;
	return (src - src0);
}
