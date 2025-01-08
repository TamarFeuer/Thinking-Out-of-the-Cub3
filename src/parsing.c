#include "../inc/game.h"

void		init_data_struct(t_data **data);
void		parse_file(t_data *data, char *file_path);
static bool	check_file_extension(char *file_path);
static bool	check_file_format(char *file_path);
static void	store_map_data(t_data *data, char *file_path);

void	init_data_struct(t_data **data)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	ft_memset(*data, 0, sizeof(t_data));
}

void	parse_file(t_data *data, char *file_path)
{
	check_file_extension(file_path);
	check_file_format(file_path);
	store_map_data(data, file_path);
	ft_print_arr(data->map_data.file_data);
	(void) data;
	printf("PARSING OK!\n");
}

static bool	check_file_extension(char *file_path)
{
	size_t	path_len;

	path_len = ft_strlen(file_path);
	if (path_len < 4)
		return (false);
	if (file_path[path_len - 4] != '.'
		|| file_path[path_len - 3] != 'c'
		|| file_path[path_len - 2] != 'u'
		|| file_path[path_len - 1] != 'b')
		return (false);
	return (true);
}

static bool	check_file_format(char *file_path)
{
	int	fd;

	fd = open(file_path, __O_DIRECTORY);
	if (fd >= 3)
	{
		close(fd);
		printf("%s", ERR_FIL_IS_DIR);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", ERR_FIL_ERR);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (true);
}

static void	store_map_data(t_data *data, char *file_path)
{
	data->map_data.nbr_of_lines = count_lines(file_path);
	data->map_data.path = file_path;
	data->map_data.file_data = (char **) ft_calloc(data->map_data.nbr_of_lines + 1, sizeof(char *));
	if (!data->map_data.file_data)
	{
		perror("store_map_data");
		exit(EXIT_FAILURE);
	}
	store_file_contents(&data->map_data, file_path);
}
