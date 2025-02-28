/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:19:43 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/01 17:41:24 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	const char *const	s0 = s;
	const char *const	a0 = accept;

	while (*s)
	{
		accept = a0;
		while (true)
		{
			if (!*accept)
				return (s - s0);
			else if (*s == *accept++)
				break ;
		}
		s++;
	}
	return (s - s0);
}
