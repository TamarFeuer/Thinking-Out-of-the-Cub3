/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx_printf.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:52:33 by rtorrent          #+#    #+#             */
/*   Updated: 2025/02/17 17:14:54 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "ft_printf.h"

static ssize_t	pad(void *dst, int (*pf)(void *, const char *, size_t),
	const char c, int n)
{
	char	*p;
	ssize_t	i;

	if (n <= 0)
		return (0);
	p = malloc(n);
	if (p)
	{
		i = pf(dst, ft_memset(p, c, n), n);
		free(p);
		return (i);
	}
	return (-1);
}

static ssize_t	sift(void *dst, int (*pf)(void *, const char *, size_t),
	const char **pformat, va_list *pap)
{
	const char *const	format0 = *pformat;
	char				str[FLD_SIZE];
	t_specf				specf;
	ssize_t				nc;

	while (**pformat && **pformat != '%')
		(*pformat)++;
	nc = pf(dst, format0, *pformat - format0);
	if (nc != -1 && **pformat)
	{
		xx_printf_read_specf(&specf, str, pformat, pap);
		if (!specf.conv)
			return (-1);
		specf.width -= specf.chrs0 + specf.num0s + specf.chrs1;
		if ((!(specf.flags & FMI) && pad(dst, pf, ' ', specf.width) == -1)
			|| pf(dst, specf.str, specf.chrs0) == -1
			|| pad(dst, pf, '0', specf.num0s) == -1
			|| pf(dst, specf.str + specf.chrs0, specf.chrs1) == -1
			|| (specf.flags & FMI && pad(dst, pf, ' ', specf.width) == -1))
			return (-1);
		nc += specf.chrs0 + specf.num0s + specf.chrs1;
		if (specf.width > 0)
			nc += specf.width;
	}
	return (nc);
}

int	xx_printf(void *dst, int (*pf)(void *, const char *, size_t),
	const char *format, va_list *pap)
{
	int	nc;
	int	nc1;

	nc = 0;
	while (*format)
	{
		nc1 = sift(dst, pf, &format, pap);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
	}
	return (nc);
}
