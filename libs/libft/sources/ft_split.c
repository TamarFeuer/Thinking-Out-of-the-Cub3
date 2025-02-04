#include "../includes/libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	int	i;
	int	counter;
	int	len;

	if (!s)
		return (0);
	i = 0;
	counter = 0;
	len = ft_strlen(s);
	while (s && i < len && s[i])
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (counter);
}

static void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static void	ft_split_words(char **arr, const char *s, char c, int wordcount)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (i < wordcount)
	{
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			k++;
		}
		arr[i] = ft_substr(s, (j - k), k);
		if (!arr[i])
			return (ft_free_arr(&arr));
		i++;
	}
	arr[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	wordcount;

	if (!s)
		return (NULL);
	wordcount = ft_count_words(s, c);
	arr = (char **) malloc ((wordcount + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	ft_split_words(arr, s, c, wordcount);
	return (arr);
}
