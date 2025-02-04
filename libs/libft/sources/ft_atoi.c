#include "../includes/libft.h"

# ifndef BASE_16
#  define BASE_16 16
# endif

int	ft_atoi(const char *nptr)
{
	int			i;
	long long	nbr;
	int			is_negative;

	i = 0;
	nbr = 0;
	is_negative = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	if (is_negative)
		return ((int) -nbr);
	return (nbr);
}

//REFACTOR
int ft_atoi_b16(const char *nptr)
{
    int i = 0;
    long long nbr = 0;
    int is_negative = 0;

    while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
        i++;
    
    if (nptr[i] == '-' || nptr[i] == '+') {
        if (nptr[i] == '-')
            is_negative = 1;
        i++;
    }
    while (nptr[i]) {
        if (ft_isdigit(nptr[i]))
            nbr = nbr * BASE_16 + (nptr[i] - '0');
        else if ((nptr[i] >= 'a' && nptr[i] <= 'f'))
            nbr = nbr * BASE_16 + (nptr[i] - 'a' + 10);
        else if ((nptr[i] >= 'A' && nptr[i] <= 'F'))
            nbr = nbr * BASE_16 + (nptr[i] - 'A' + 10);
        else
            break;
        i++;
    }
    if (is_negative)
        return (int)-nbr;
    return (int)nbr;
}
