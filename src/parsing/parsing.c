#include "../../inc/game.h"

void		init_data_struct(t_data **data);
void		parse_file(t_game *game, t_data *data, char *file_path);
bool		check_file_format(char *file_path);
static void	copy_file_contents(t_data *data, char *file_path);
int			count_lines(char *file_path);
void		copy_line_by_line(t_mapdata *mapdata, int fd);

void	init_data_struct(t_data **data)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	ft_memset(*data, 0, sizeof(t_data));
}
void	parse_file(t_game *game, t_data *data, char *file_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_file_format(file_path);
	copy_file_contents(data, file_path);
	parse_identifiers(data, &i, &j);
	parse_map(game, data, &i, &j);
	if (!check_map_validity(game, data))
		printf("PARSING NOT OK!\n");
	else
		printf("PARSING OK!\n");

<<<<<<< HEAD
	//MINIMAP struct init
	data->minimap_data.width = data->map_data.cols * game->cell_size;
	data->minimap_data.height = data->map_data.rows * game->cell_size;
	data->minimap_data.x_start = 0;
	data->minimap_data.x_end = data->minimap_data.x_start + data->minimap_data.width;
	data->minimap_data.y_start = 0;
	data->minimap_data.y_end = data->minimap_data.y_start + data->minimap_data.height;
	data->minimap_data.max_height = SCREEN_HEIGHT/4;
	data->minimap_data.max_width = SCREEN_WIDTH/4;
=======
	// //MINIMAP struct init
	// game->data->minimap_data.width = game->data->map_data.cols * game->cell_size;
	// printf ("in parsing: game->data->minimap_data.width %d\n", game->data->minimap_data.width);
	// game->data->minimap_data.height = game->data->map_data.rows * game->cell_size;
	// game->data->minimap_data.x_start = 0;
	// game->data->minimap_data.x_end = game->data->minimap_data.x_start + game->data->minimap_data.width;
	// game->data->minimap_data.y_start = 0;
	// game->data->minimap_data.y_end = game->data->minimap_data.y_start + game->data->minimap_data.height;
	// game->data->minimap_data.max_height = SCREEN_HEIGHT/4;
	// game->data->minimap_data.max_width = SCREEN_WIDTH/4;
>>>>>>> resizing_mmap2
	
	// ft_print_arr(data->map_data.map);
}

bool	check_file_format(char *file_path)
{
	int	fd;

	fd = open(file_path, __O_DIRECTORY);
	if (fd >= 3)
	{
		close(fd);
		printf("%s\n", ERR_IS_DIR);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		printf("check_file_format - %s\n", ERR_OPEN);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (true);
}

static void	copy_file_contents(t_data *data, char *file_path)
{
	int	fd;

	data->map_data.total_lines = count_lines(file_path);
	data->map_data.path = file_path;
	data->map_data.file_data = (char **) ft_calloc(data->map_data.total_lines + 1, sizeof(char *));
	if (!data->map_data.file_data)
	{
		perror("copy_file_contents");
		exit(EXIT_FAILURE);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("copy_file_contents");
		exit(EXIT_FAILURE);
	}
	copy_line_by_line(&data->map_data, fd);
	close (fd); //Check if it fails
}

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

void	copy_line_by_line(t_mapdata *mapdata, int fd)
{
	char	*curr_line;
	size_t	line_len;
	int		row;
	int		col;
	int		i;

	curr_line = get_next_line(fd);
	row = 0;
	while (curr_line)
	{
		line_len = ft_strlen(curr_line);
		mapdata->file_data[row] = (char *) ft_calloc(line_len + 1, sizeof(char));
		if (!mapdata->file_data[row])
		{
			perror("copy_line_by_line");
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
