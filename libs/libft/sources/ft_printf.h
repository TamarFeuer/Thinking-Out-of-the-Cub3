/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:00:28 by rtorrent          #+#    #+#             */
/*   Updated: 2025/02/17 17:16:36 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* ************************************************************************** */

# include "../includes/libft.h"

/* ************************************************************************** */

// FLD_SIZE: buffer size for non-string conversions
# define FLD_SIZE 32

// MSPEC: maximum values for the optional field width and precision are
//        (MSPEC - 1) * 10 + 9
# define MSPEC 1000

/*
  specifier flags:
	FNO: #
	FZE: 0
	FMI: -
	FSP: space
	FPL: +
*/

# define FNO 001
# define FZE 002
# define FMI 004
# define FSP 010
# define FPL 020

// specifiers

typedef struct s_specf
{
	char			*str;
	long			ival;
	unsigned int	flags;
	size_t			chrs0;
	size_t			num0s;
	size_t			chrs1;
	int				width;
	int				prec;
	char			conv;
}	t_specf;

/* ************************************************************************** */

// principal routines for the 'printf' family of functions (stdio.h)

int		xx_printf(void *dst, int (*pf)(void *, const char *, size_t),
			const char *format, va_list *pap);
void	xx_printf_read_specf(t_specf *const pspecf, char *const str,
			const char **const pp, va_list *pap);

/* ************************************************************************** */

#endif
