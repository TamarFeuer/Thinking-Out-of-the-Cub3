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
	int		row;
	int		col;

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

	row = 0;
	while (map[*i])
	{
		data->map_data.map[row] = (char *) malloc(data->map_data.cols + 1);
		if (!data->map_data.map[row])
			printf("%s\n", ERR_MEM_ALL);

		//Checks that there's no empty line somewhere in between the map.
		*j = 0;
		while (map[*i][*j] != '\0' && (map[*i][*j] == '\t' || map[*i][*j] == ' '))
			*j += 1;
		if (map[*i][*j] == '\n')
			break ;

		*j = 0;
		col = 0;
		while (map[*i][*j] != '\0' && map[*i][*j] != '\n')
		{
			//Converts tabs into 4 spaces.
			if (map[*i][*j] == '\t')
			{
				data->map_data.map[row][col] = ' ';
				data->map_data.map[row][col + 1] = ' ';
				data->map_data.map[row][col + 2] = ' ';
				data->map_data.map[row][col + 3] = ' ';
				col += 4;
			}
			else //Copies the contents of the map
			{
				data->map_data.map[row][col] = map[*i][*j];
				col++;
			}
			*j += 1;
		}

		//Fills the rest of the line with empty spaces
		while (col < data->map_data.cols - 1)
			data->map_data.map[row][col++] = ' ';
		data->map_data.map[row][col] = '\0';
		*i += 1;
		row++;
	}
	data->map_data.map[row] = NULL;

	skip_nl_and_whitespaces(map, i, j);
	skip_whitespaces(map, *i, j);

	// ft_print_arr(data->map_data.map);

	if (map[*i] && map[*i][*j] && map[*i][*j] != '\n')
	{
		printf("There's an empty line splitting the map.\n");
		return ;
	}
}
