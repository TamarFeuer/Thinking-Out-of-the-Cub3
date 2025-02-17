/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx_printf_read_specf.c                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:36:33 by rtorrent          #+#    #+#             */
/*   Updated: 2025/02/17 17:15:19 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "ft_printf.h"

static void	ntoa(t_specf *const psp, const char c, const char *hex, const int b)
{
	int				n;
	unsigned long	uval;

	n = FLD_SIZE;
	uval = psp->ival;
	if (c == 'u' || c == 'x' || c == 'X')
		uval = (unsigned int)psp->ival;
	else if ((c == 'i' || c == 'd') && psp->ival < 0)
		uval = -psp->ival;
	if (!uval && psp->prec)
		psp->str[--n] = '0';
	while (uval)
	{
		psp->str[--n] = hex[uval % b];
		uval /= b;
	}
	psp->chrs1 = FLD_SIZE - n;
	ft_memmove(psp->str + psp->chrs0, psp->str + n, psp->chrs1);
	n = psp->width - psp->chrs0 - psp->chrs1;
	if ((int)psp->chrs1 < psp->prec)
		psp->num0s = psp->prec - psp->chrs1;
	else if (psp->prec < 0 && (psp->flags & (FZE | FMI)) == FZE && n > 0)
		psp->num0s = n;
}

static void	fill_number_field(t_specf *const pspecf, const char c, va_list *pap)
{
	if (c == 'd' || c == 'i' || c == 'u')
	{
		pspecf->ival = va_arg(*pap, int);
		if (c != 'u' && pspecf->ival < 0)
			pspecf->str[pspecf->chrs0++] = '-';
		else if (c != 'u' && pspecf->flags & FPL)
			pspecf->str[pspecf->chrs0++] = '+';
		else if (c != 'u' && pspecf->flags & FSP)
			pspecf->str[pspecf->chrs0++] = ' ';
		return (ntoa(pspecf, c, "0123456789", 10));
	}
	if (c != 'p')
		pspecf->ival = va_arg(*pap, int);
	else
		pspecf->ival = (long)va_arg(*pap, void *);
	if ((c == 'x' && pspecf->flags & FNO && pspecf->ival)
		|| (c == 'p' && pspecf->ival != (long)(void *)0))
		pspecf->chrs0 += ft_strlcpy(pspecf->str, "0x", 3);
	else if (c == 'X' && pspecf->flags & FNO && pspecf->ival)
		pspecf->chrs0 += ft_strlcpy(pspecf->str, "0X", 3);
	if (c == 'X')
		return (ntoa(pspecf, c, "0123456789ABCDEF", 16));
	if (c != 'p' || pspecf->ival != (long)(void *)0)
		return (ntoa(pspecf, c, "0123456789abcdef", 16));
	pspecf->chrs1 += ft_strlcpy(pspecf->str, "(nil)", 6);
}

static void	fill_text_field(t_specf *const pspecf, const char c, va_list *pap)
{
	if (c == 'c')
		pspecf->str[pspecf->chrs0++] = va_arg(*pap, int);
	else if (c == 's')
	{
		pspecf->str = va_arg(*pap, char *);
		if (pspecf->str)
		{
			pspecf->chrs1 = ft_strlen(pspecf->str);
			if (0 <= pspecf->prec && pspecf->prec < (int)pspecf->chrs1)
				pspecf->chrs1 = pspecf->prec;
		}
		else
		{
			pspecf->str = "(null)";
			if (pspecf->prec < 0 || pspecf->prec >= 6)
				pspecf->chrs1 = 6;
		}
	}
	else
	{
		pspecf->str[pspecf->chrs0++] = c;
		pspecf->width = 0;
	}
}

void	xx_printf_read_specf(t_specf *const pspecf, char *const str,
		const char **const pformat, va_list *pap)
{
	static const char			fchars[] = "#0- +";
	static const unsigned int	fuints[] = {FNO, FZE, FMI, FSP, FPL, 0};

	ft_bzero(pspecf, sizeof(t_specf));
	pspecf->str = str;
	while (*(++*pformat) && ft_strchr(fchars, **pformat))
		pspecf->flags |= fuints[ft_strchr(fchars, **pformat) - fchars];
	while (ft_isdigit(**pformat) && pspecf->width < MSPEC)
		pspecf->width = pspecf->width * 10 + *(*pformat)++ - '0';
	if (**pformat != '.')
		pspecf->prec = -1;
	else
	{
		++*pformat;
		while (ft_isdigit(**pformat) && pspecf->prec < MSPEC)
			pspecf->prec = pspecf->prec * 10 + *(*pformat)++ - '0';
	}
	pspecf->conv = *(*pformat)++;
	if (pspecf->conv == 'd' || pspecf->conv == 'i' || pspecf->conv == 'u'
		|| pspecf->conv == 'x' || pspecf->conv == 'X' || pspecf->conv == 'p')
		fill_number_field(pspecf, pspecf->conv, pap);
	else if (ft_isprint((int)pspecf->conv))
		fill_text_field(pspecf, pspecf->conv, pap);
}
