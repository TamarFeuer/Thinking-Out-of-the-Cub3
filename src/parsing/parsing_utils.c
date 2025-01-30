#include "../../inc/game.h"

void	ft_print_arr(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	skip_nl_and_whitespaces(char **arr, int *i, int *j)
{
	if (!arr)
		return ;
	while (arr[*i] && arr[*i][*j])
	{
		if (arr[*i][*j] == ' ' || arr[*i][*j] == '\t')
			*j += 1;
		else if (arr[*i][*j] == '\n')
		{
			*j = 0;
			*i += 1;
		}
		else
			break ;
	}
}

void	skip_whitespaces(char **arr, int i, int *j)
{
	if (!arr)
		return ;
	while (arr[i] && arr[i][*j])
	{
		if (arr[i][*j] == ' ' || arr[i][*j] == '\t')
			*j += 1;
		else
			break ;
	}
}
