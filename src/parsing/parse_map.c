#include "../../inc/game.h"

void	count_map_rows(t_game *game, t_data *data, int row)
{
	char	**file;
	int		col;

	(void)data;
	file = game->data->map_data.file_data;
	if (!file)
		return ;
	col = 0;
	skip_nl_and_whitespaces(file, &row, &col);

	//Start counting the number of rows
	game->data->map_data.rows = 0;
	while (file[row])
	{
		col = 0;
		while (file[row][col] == ' ' || file[row][col] == '\t')
			col++;
		if (file[row][col] == '\n')
			break ;
		row++;
		game->data->map_data.rows++;
	}
	// printf("count_map_rows: %d\n", data->map_data.rows);
}

void	count_map_cols(t_game *game, t_data *data, int row)
{
	char	**file;
	int		col;

	(void)data;
	file = game->data->map_data.file_data;
	if (!file)
		return ;
	col = 0;
	skip_nl_and_whitespaces(file, &row, &col);
	game->data->map_data.cols = 0;
	while (file[row])
	{
		col = 0;
		while (file[row][col])
		{
			if (file[row][col] == '\t')
				col += 4;
			else
				col++;
			printf("col is %d\n", col);
		}
		if (--col > game->data->map_data.cols)
			game->data->map_data.cols = col;
		row++;
	}
	// printf("count_map_cols: %d\n", game->data->map_data.cols);
}

void parse_map(t_game *game, t_data *data, int *i, int *j)
{
	char	**map;
	int		row;
	int		col;

	(void)data;
	count_map_rows(game, data, *i);
	count_map_cols(game, data, *i);

	//Allocate memory for the map array.
	game->data->map_data.map = (char **) malloc(sizeof(char *) * (game->data->map_data.rows + 1));
	if (!game->data->map_data.map)
		printf("%s\n", ERR_MEM_ALL);

	//Assign the array with the file contents to a shorter variable.
	map = game->data->map_data.file_data;
	if (!map)
		return ;

	skip_nl_and_whitespaces(map, i, j);

	//We're at the map portion. If it does not begin with a digit, in particular a 1, it's an invalid map.
	if (map[*i] && map[*i][*j] && !ft_isdigit(map[*i][*j]))
		printf("The map does not begin with a digit.\n");

	row = 0;
	while (map[*i])
	{
		game->data->map_data.map[row] = (char *) malloc(game->data->map_data.cols);
		if (!game->data->map_data.map[row])
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
				game->data->map_data.map[row][col] = ' ';
				game->data->map_data.map[row][col + 1] = ' ';
				game->data->map_data.map[row][col + 2] = ' ';
				game->data->map_data.map[row][col + 3] = ' ';
				col += 4;
			}
			else //Copies the contents of the map
			{
				if (ft_is_pos_identifier(map[*i][*j]))
				{
<<<<<<< HEAD
					game->player.p_pos.x = (double) col;
					game->player.p_pos.y = (double) row;
=======
					game->data->player.p_pos.x = (double) col;
					game->data->player.p_pos.y = (double) row;
>>>>>>> resizing_mmap2
					if (map[*i][*j] == 'N')
					{

						game->data->player.angle = M_PI / 2;
						game->data->player.angle_quad = 2;
					}
					else if (map[*i][*j] == 'W')
					{
						game->data->player.angle = M_PI;
						game->data->player.angle_quad = 3;
					}
					else if (map[*i][*j] == 'S')
					{
						game->data->player.angle = 3 * M_PI / 2;
						game->data->player.angle_quad = 4;
					}
					else if (map[*i][*j] == 'E')
					{
						game->data->player.angle = 0;
						game->data->player.angle_quad = 1;
					}
					map[*i][*j] = '0';
				}
				game->data->map_data.map[row][col] = map[*i][*j];
				col++;
			}
			*j += 1;
		}
<<<<<<< HEAD
		//printf ("player angle is %f\n", data->player.angle);
=======
		printf ("player angle is %f\n", game->data->player.angle);
>>>>>>> resizing_mmap2
		//Fills the rest of the line with empty spaces
		while (col < game->data->map_data.cols)
		{
			game->data->map_data.map[row][col++] = ' ';
		}
		game->data->map_data.map[row][col] = '\0';
		*i += 1;
		row++;
	}
	game->data->map_data.map[row] = NULL;

	skip_nl_and_whitespaces(map, i, j);
	skip_whitespaces(map, *i, j);

	// ft_print_arr(data->map_data.map);

	if (map[*i] && map[*i][*j] && map[*i][*j] != '\n')
	{
		printf("There's an empty line splitting the map.\n");
		return ;
	}
}
