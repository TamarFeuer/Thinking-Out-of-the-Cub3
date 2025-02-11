#include "../../inc/game.h"

int		count_lines(char *file_path);
bool	is_pos_identifier(char c);
void	ft_print_arr(char **arr);
void	skip_nl_and_whitespaces(char **arr, int *i, int *j);
void	skip_whitespaces(char **arr, int i, int *j);

int	count_lines(char *file_path)
{
	int		fd;
	int		total_lines;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("count_lines");
		exit(EXIT_FAILURE);
	}
	total_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		total_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (total_lines);
}

bool	is_pos_identifier(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

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
