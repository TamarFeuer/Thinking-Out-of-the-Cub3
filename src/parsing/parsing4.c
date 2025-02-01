#include "../../inc/game.h"

void	count_map_rows(t_data *data, int row)
{
	char	**file;
	int		col;

	file = data->map_data.file_data;
	if (!file)
		return ;
	col = 0;
	skip_nl_and_whitespaces(file, &row, &col);

	//Start counting the number of rows
	data->map_data.rows = 0;
	while (file[row])
	{
		col = 0;
		while (file[row][col] == ' ' || file[row][col] == '\t')
			col++;
		if (file[row][col] == '\n')
			break ;
		row++;
		data->map_data.rows++;
	}
	printf("count_map_rows: %d\n", data->map_data.rows);
}

void	count_map_cols(t_data *data, int row)
{
	char	**file;
	int		col;

	file = data->map_data.file_data;
	if (!file)
		return ;
	col = 0;
	skip_nl_and_whitespaces(file, &row, &col);
	data->map_data.cols = 0;
	while (file[row])
	{
		col = 0;
		while (file[row][col])
		{
			if (file[row][col] == '\t')
				col += 4;
			else
				col++;
		}
		if (col > data->map_data.cols)
			data->map_data.cols = col;
		row++;
	}
	printf("count_map_cols: %d\n", data->map_data.cols);
}

void parse_map(t_data *data, int *i, int *j)
{
	char	**map;
	int		len = 0;
	int		k;
	int		l;
	int		m;

	count_map_rows(data, *i);
	count_map_cols(data, *i);

	//Allocate memory for the map array.
	data->map_data.map = (char **) malloc(sizeof(char *) * (data->map_data.rows + 1));
	if (!data->map_data.map)
		printf("%s\n", ERR_MEM_ALL);

	//Assign the array with the file contents to a shorter variable.
	map = data->map_data.file_data;
	if (!map)
		return ;

	skip_nl_and_whitespaces(map, i, j);

	//We're at the map portion. If it does not begin with a digit, in particular a 1, it's an invalid map.
	if (map[*i] && map[*i][*j] && !ft_isdigit(map[*i][*j]))
		printf("The map does not begin with a digit.\n");

	*j = 0;
	k = 0;
	while (map[*i] && map[*i][*j])
	{
		l = *j;
		len = 0;
		while (map[*i][l] != '\0' && map[*i][l] != '\n')
		{
			if (!ft_isdigit(map[*i][l]) && !ft_is_pos_identifier(map[*i][l]) && map[*i][l] != ' ' && map[*i][l] != '\t') //later check that the pos identifier is not repeated?
				printf("There's an element in the map that's not valid.\n");
			else if (map[*i][l] == '\t')
				len += 4;
			else
				len++;
			l++;
		}

		//Allocated memory for the line.
		data->map_data.map[k] = (char *) malloc(len + 1);
		if (!data->map_data.map[k])
			printf("%s\n", ERR_MEM_ALL);

		//Copies the line contents into the new map variable (in the data structure)
		l = 0;
		while (map[*i][*j] != '\0' && map[*i][*j] != '\n')
		{
			if (!ft_isdigit(map[*i][*j]) && !ft_is_pos_identifier(map[*i][*j]) && map[*i][*j] != ' ' && map[*i][*j] != '\t')
				printf("There's an element in the map that's not a digit: %c.\n", map[k][*j]);
			else if (map[*i][*j] != '\t')
				data->map_data.map[k][l] = map[*i][*j];
			else if (map[*i][*j] == '\t')
			{
				m = -1;
				while (m < 4)
					data->map_data.map[k][l + ++m] = ' ';
				l += m - 1;
			}
			*j += 1;
			l++;
		}
		data->map_data.map[k][l] = '\0';
		k++;
		*i += 1;
		*j = 0;
	}
	data->map_data.map[k] = NULL;
	// ft_print_arr(data->map_data.map);
}
