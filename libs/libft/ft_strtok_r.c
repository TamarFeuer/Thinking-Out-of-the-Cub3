/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:54:01 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/26 22:26:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *s, const char *delim, char **saveptr)
{
	char	*s_1;

	if (!s)
		s = *saveptr;
	s += ft_strspn(s, delim);
	if (!*s)
	{
		*saveptr = s;
		return (NULL);
	}
	s_1 = s + ft_strcspn(s, delim);
	if (*s_1)
		*s_1++ = '\0';
	*saveptr = s_1;
	return (s);
}
