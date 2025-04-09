#include "../inc/game.h"

static unsigned int	count_int_length(long long n)
{
	unsigned int	i;

	i = 0;
	if (n < 0)
	{
		n *= (-1);
		i++;
	}
	if (n == 0)
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_itoa2(char *str, int n)
{
	long long		nbr;
	unsigned int	nbr_len;
	unsigned int	i;

	nbr = n;
	nbr_len = count_int_length(nbr);
	str[nbr_len] = '\0';
	i = 0;
	if (nbr == 0)
	{
		str[i] = '0';
		return ;
	}
	if (nbr < 0)
	{
		str[i] = '-';
		nbr *= (-1);
	}
	while (i < nbr_len && nbr > 0)
	{
		str[nbr_len - 1 - i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
}

static void	ft_ftoa(char *str, float n, int precision)
{
    int int_part = (int)n;  // Extract the integer part
    float decimal_part = n - int_part;  // Extract the decimal part
    int i = 0, digit;

    // Handle the integer part (negative or positive)
    if (int_part < 0)
    {
        str[i++] = '-';  // Add the minus sign for negative numbers
        int_part = -int_part;  // Work with positive integer part for easier handling
    }

    // Convert the integer part to string (reverse order)
    int temp_int_part = int_part;
    int num_digits = 0;
    while (temp_int_part > 0)
    {
        num_digits++;
        temp_int_part /= 10;
    }

    // If the integer part is 0, we still need to handle it
    if (num_digits == 0)
        str[i++] = '0';

    for (int j = 0; j < num_digits; j++)
    {
        str[i + num_digits - 1 - j] = (int_part % 10) + '0';  // Get last digit
        int_part /= 10;
    }
    i += num_digits;

    // Add the decimal point
    str[i++] = '.';

    // Handle the fractional part (multiply by 10 to extract digits)
    for (int j = 0; j < precision; j++)
    {
        decimal_part *= 10;
        digit = (int)decimal_part;
        str[i++] = digit + '0';  // Convert digit to char
        decimal_part -= digit;  // Remove the integer part from decimal part
    }

    // Null-terminate the string
    str[i] = '\0';
}

void	print_stats(t_game *game)
{
	char	info[LOG];
	char	*p;

	p = info + ft_strlcpy(info, "Angle: ", LOG);
	ft_ftoa(p, game->player.angle / M_PI, 6);
	p = info + ft_strlcat(info, "PI X: ", LOG);
	ft_itoa2(p, (game->player.pos.x - X_START));
	p = info + ft_strlcat(info, " Y: ", LOG);
	ft_itoa2(p, (game->player.pos.y - Y_START));
	game->stats = mlx_put_string(game->mlx, info, 10, 10);
}
