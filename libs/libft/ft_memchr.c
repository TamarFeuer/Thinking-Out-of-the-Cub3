/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:08:50 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/13 23:43:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*us;
	const unsigned char	uc = c;

	us = s;
	while (n--)
	{
		if (*us == uc)
			return ((void *)us);
		us++;
	}
	return (NULL);
}
