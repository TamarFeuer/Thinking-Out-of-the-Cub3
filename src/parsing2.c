#include "../inc/game.h"

int	count_lines(char *file_path)
{
	int		fd;
	int		nbr_of_lines;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("count_lines");
		exit(EXIT_FAILURE);
	}
	nbr_of_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		nbr_of_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nbr_of_lines);
}

void	store_file_contents(t_mapdata *mapdata, char *file_path)
{
	int		fd;
	char	*curr_line;
	size_t	line_len;
	int		row;
	int		col;
	int		i;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("store_file_contents");
		exit(EXIT_FAILURE);
	}
	curr_line = get_next_line(fd);
	row = 0;
	while (curr_line)
	{
		line_len = ft_strlen(curr_line);
		mapdata->file_data[row] = (char *) ft_calloc(line_len + 1, sizeof(char));
		if (!mapdata->file_data[row])
		{
			perror("store_file_contents");
			exit(EXIT_FAILURE);
		}
		i = 0;
		col = 0;
		while(curr_line[i] != '\0')
			mapdata->file_data[row][col++] = curr_line[i++];
		row++;
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	mapdata->file_data[row] = NULL;
}
