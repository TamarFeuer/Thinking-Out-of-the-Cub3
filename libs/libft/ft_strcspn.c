/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:43:06 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/01 17:53:10 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	const char *const	s0 = s;
	const char *const	r0 = reject;

	while (*s)
	{
		reject = r0;
		while (*reject)
			if (*s == *reject++)
				return (s - s0);
		s++;
	}
	return (s - s0);
}
