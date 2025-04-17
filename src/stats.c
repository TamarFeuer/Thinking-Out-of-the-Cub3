/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:14:10 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/17 18:14:12 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static unsigned int	count_uint_length(unsigned long long n)
{
	unsigned int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/**
 * @brief Converts a non-negative integer to a null-terminated string.
 *
 * @param str The buffer to write the string into. Must be large enough.
 *            Use count_uint_length(n) + 1 for required size.
 * @param n The non-negative integer to convert.
 */
static void	ft_uitoa(char *str, unsigned int n) // Use unsigned int
{
	unsigned long long	nbr;
	unsigned int		len;
	unsigned int		i;

	nbr = n;
	len = count_uint_length(nbr);
	str[len] = '\0';
	i = len - 1;
	if (nbr == 0)
	{
		str[0] = '0';
		return ;
	}
	while (nbr > 0)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		if (i > 0)
			i--;
	}
}

static void	ft_ftoa_fixed(char *str, float n, int decimals)
{
	unsigned int	int_part;
	float			decimal_part;
	int				i;
	int				k;
	int				digit;

	int_part = (unsigned int)n;
	ft_uitoa(str, int_part);
	i = 0;
	while (str[i] != '\0')
		i++;
	decimal_part = n - (float)int_part;
	str[i++] = '.';
	k = 0;
	while (k < decimals)
	{
		decimal_part *= 10.0f;
		digit = (int)decimal_part;
		str[i++] = digit + '0';
		decimal_part -= (float)digit;
		k++;
	}
	str[i] = '\0';
}

void	print_stats(t_game *game)
{
	char	info[LOG];
	char	*p;

	p = info + ft_strlcpy(info, "Angle: ", LOG);
	ft_ftoa_fixed(p, game->player.angle / PI, 6);
	p = info + ft_strlcat(info, "PI X: ", LOG);
	ft_uitoa(p, game->player.pos.x);
	p = info + ft_strlcat(info, " Y: ", LOG);
	ft_uitoa(p, game->player.pos.y);
	game->stats = mlx_put_string(game->mlx, info, 10, 10);
}
