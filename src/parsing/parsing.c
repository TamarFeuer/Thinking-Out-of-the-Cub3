#include "../../inc/game.h"

void			parse_file(t_data *data, char *file_path);
static t_ecode	check_file_extension(char *file_path, t_ecode *err_no);
t_ecode 		check_file_format(char *file_path, t_ecode *err_no);
static void		copy_file_contents(t_data *data, char *file_path);
t_ecode			copy_line_by_line(t_mapdata *mapdata, int fd);

void	parse_file(t_data *data, char *file_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_file_extension(file_path, &data->err_no) && !data->is_debug)
		clean_and_exit(data, ECODE_CHECK_FILE_EXTENSION);
	if (check_file_format(file_path, &data->err_no) && !data->is_debug)
		clean_and_exit(data, ECODE_CHECK_FILE_FORMAT);
	copy_file_contents(data, file_path);
	if (parse_identifiers(data, &i, &j) && !data->is_debug)
		clean_and_exit(data, ECODE_PARSE_IDENTIFIERS);
	if (parse_map(data, data->game, &i, &j) && !data->is_debug)
		clean_and_exit(data, ECODE_PARSE_MAP);
	if (check_map_validity(data) && !data->is_debug)
		clean_and_exit(data, ECODE_CHECK_MAP_VALIDITY);
	if (init_minimap_struct(data) && !data->is_debug)
		clean_and_exit(data, ECODE_INIT_MINIMAP_STRUCT);
	// ft_print_arr(data->map_data.map);
}

static t_ecode	check_file_extension(char *file_path, t_ecode *err_no)
{
	size_t	path_len;

	path_len = ft_strlen(file_path);
	if (path_len < 5)
		return (*err_no = ECODE_INV_LEN, ECODE_INV_LEN);
	if (file_path[path_len - 4] != '.'
		|| file_path[path_len - 3] != 'c'
		|| file_path[path_len - 2] != 'u'
		|| file_path[path_len - 1] != 'b')
		return (*err_no = ECODE_INV_LEN, ECODE_INV_LEN);
	return (ECODE_SUCCESS);
}

t_ecode	check_file_format(char *file_path, t_ecode *err_no)
{
	int	fd;

	fd = open(file_path, __O_DIRECTORY);
	if (fd >= 3)
	{
		close(fd);
		*err_no = ECODE_IS_DIR;
		return (ECODE_IS_DIR);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		*err_no = ECODE_OPEN;
		return (ECODE_OPEN);
	}
	close(fd);
	return (ECODE_SUCCESS);
}

static void	copy_file_contents(t_data *data, char *file_path)
{
	int	fd;

	data->map_data.total_lines = count_lines(file_path);
	data->map_data.path = file_path;
	data->map_data.file_data = (char **) ft_calloc(data->map_data.total_lines + 1, sizeof(char *));
	if (!data->map_data.file_data && !data->is_debug)
		clean_and_exit(data, ECODE_COPY_FILE_CONTENTS);
	fd = open(file_path, O_RDONLY);
	if (fd < 0 && !data->is_debug)
		clean_and_exit(data, ECODE_COPY_FILE_CONTENTS);
	if (copy_line_by_line(&data->map_data, fd) && !data->is_debug)
		clean_and_exit(data, ECODE_COPY_LINE_BY_LINE);
	close (fd); //Check if it fails
}

t_ecode	copy_line_by_line(t_mapdata *mapdata, int fd)
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
			return (ECODE_COPY_LINE_BY_LINE);
		i = 0;
		col = 0;
		while(curr_line[i] != '\0')
			mapdata->file_data[row][col++] = curr_line[i++];
		row++;
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	mapdata->file_data[row] = NULL;
	return (ECODE_SUCCESS);
}
