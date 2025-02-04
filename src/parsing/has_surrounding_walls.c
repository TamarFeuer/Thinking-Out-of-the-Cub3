#include "../../inc/game.h"

bool	check_col_above(char **map, int row, int col);
bool	check_col_below(t_data *data, char **map, int row, int col);
bool	check_right_col(char **map, int row, int col);
bool	check_left_col(char **map, int row, int col);


bool	is_surrounded_by_walls(t_data *data, char **map)
{
	int	row;
	int	col;

	if (!map)
		return (false);
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			//The first row should be full of 1s or spaces
			if (row == 0 && map[row][col] == '0')
			{
				printf("ROW #%i doesn't have a wall where it should.\n", row);
				printf("is_surrounded_by_walls\n");
				return (false);
			}
			//Checks for when the tile is a walkable space
			else if (row > 0 && (map[row][col] == '0' || map[row][col] == ' '))
			{
				// ft_print_arr(map);
				printf("ROW: %d, COL: %d, |%c|\n", row, col, map[row][col]);
				if (!check_col_above(map, row, col))
					return (false);
				if (!check_col_below(data, map, row, col))
					return (false);
				if (!check_right_col(map, row, col))
					return (false);
				if (!check_left_col(map, row, col))
					return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}

/**
 * This function checks the column above for a wall, recursively.
 * If the original column is a 0, the one directly above cannot be a space.
 */
bool	check_col_above(char **map, int row, int col)
{
	//Checks the map's NULLITY
	if (!map || !*map)
	{
		printf("NULL MAP! check_col_above\n");
		return (false);
	}
	//This is also for map's nullity, but with a different error message
	if (row - 1 < 0)
	{
		printf("The map is not surrounded by walls... check_col_above\n");
		return (false);
	}
	
	if (map[row][col] == '0' && row - 1 >= 0)
	{
		if (map[row - 1][col] == '1')
		{
			// printf("Check_col_Above\n");
			return (true);
		}
		if (map[row - 1][col] == '0' || ft_is_pos_identifier(map[row - 1][col]))
			return (check_col_above(map, row - 1, col));
		else if (map[row - 1][col] == ' ')
		{
			printf("There's a space where there should be a wall. check_col_above\n");
			return (false);
		}
	}
	else if (map[row][col] == ' ' && row - 1 >= 0)
	{
		if (map[row - 1][col] == '1' || (row == 1 && map[row - 1][col] == ' ')) //This is hardcoded...
			return (true);
		if (map[row - 1][col] == ' ')
			return (check_col_above(map, row - 1, col));
		else if (map[row - 1][col] == '0' || ft_is_pos_identifier(map[row - 1][col]))
		{
			printf("There's a 0 or N/E/W/S where there should be a wall. check_col_above\n");
			return (false);
		}
	}
	return (false);
}

bool	check_col_below(t_data *data, char **map, int row, int col)
{
	if (!map || !*map)
	{
		printf("NULL MAP! check_col_below\n");
		return (false);
	}
	if (row + 1 >= data->map_data.rows)
	{
		printf("The map didn't have a wall where it should, and it ran out of lines. check_col_below\n");
		return (false);
	}

	if (map[row][col] == '0' && row + 1 < data->map_data.rows)
	{
		if (map[row + 1][col] == '1')
		{
			// printf("Check_col_below\n");
			return (true);
		}
		if (map[row + 1][col] == '0' || ft_is_pos_identifier(map[row + 1][col]))
			return (check_col_below(data, map, row + 1, col));
		else if (map[row + 1][col] == ' ')
		{
			printf("There's a space where there should be a wall. check_col_below\n");
			return (false);
		}
	}
	else if (map[row][col] == ' ' && row + 1 < data->map_data.rows)
	{
		if (map[row + 1][col] == '1')
			return (true);
		if (map[row + 1][col] == ' ')
			return (check_col_below(data, map, row + 1, col));
		else if (map[row + 1][col] == '0' || ft_is_pos_identifier(map[row + 1][col]))
		{
			printf("There's a 0 or N/E/W/S where there should be a wall. check_col_below\n");
			return (false);
		}
	}


	// else if (row + 1 < data->map_data.rows && (map[row + 1][col] == '0' || map[row + 1][col] == ' '))
	// 	return (check_col_below(data, map, row + 1, col));
	// else if (row + 1 < data->map_data.rows && map[row + 1][col] == '1')
	// 	return (true);
	return (false);
}

bool	check_right_col(char **map, int row, int col)
{
	int	i;
	int	len;

	//Checks for the map's nullity
	if (!map || !*map || row < 0 || col < 0)
	{
		printf("NULL MAP!\n");
		return (false);
	}

	//Checks if the last column of the row is a walkable space
	len = ft_strlen(map[row]);
	if (map[row][len - 1] && map[row][len - 1] == '0')
	{
		printf("The column ends with a 0. check_right_col\n");
		return (false);
	}

	//Checks if there's a wall somewhere to the right of a walkable space
	if (map[row][col] && (map[row][col] == '0'))
	{
		i = 0;
		while (map[row][col + i] != '\0' && map[row][col + i] != '\n')
		{
			//If there's a space right after a 0, that 0 and that space are not surrounded by walls.
			if (map[row][col + i] == ' ')
			{
				printf("There's a space after a 0 in check_right_col\n");
				return (false);
			}
			else if (map[row][col + i] == '1')
				return (true);
			i++;
		}
	}

	//Checks if there's a wall somewhere to the right of a empty space
	else if (map[row][col] && (map[row][col] == ' '))
	{
		i = 0;
		while (map[row][col + i] != '\0' && map[row][col + i] != '\n')
		{
			if (map[row][col + i] == '0')
			{
				printf("There's a 0 after a space in check_right_col\n");
				return (false);
			}
			else if (map[row][col + i] == '1')
				return (true);
			i++;
		}
	}
	return (false);
}

bool	check_left_col(char **map, int row, int col)
{
	int	i;

	//Checks for the map's nullity
	if (!map || !*map || row < 0 || col < 0)
	{
		printf("NULL MAP!\n");
		return (false);
	}

	//Checks if the row begins with a 0.
	i = 0;
	while (map[row][col] && map[row][i] == ' ')
		i++;
	if (map[row][col] && map[row][i] == '0')
	{
		printf("The column begins with a 0. check_left_col\n");
		return (false);
	}


	if (map[row][col] && (map[row][col] == '0'))
	{
		i = 0;
		while (col - i >= 0 && map[row][col - i] != '\0')
		{
			//If there's a space right before a 0, that 0 and that space are not surrounded by walls.
			if (map[row][col - i] == ' ')
			{
				printf("There was a space before a wall, to the left. check_left_col\n");
				return (false);
			}
			else if (map[row][col - i] == '1')
				return (true);
			i++;
		}
	}

	else if (map[row][col] && map[row][col] == ' ')
	{
		i = 0;
		while (col - i >= 0 && map[row][col - i] != '\0')
		{
			if (map[row][col - i] == '0')
			{
				printf("There's a 0 before a space in check_left_col\n");
				return (false);
			}
			else if (map[row][col + i] == '1')
				return (true);
			i++;
		}
	}

	return (false);
}
