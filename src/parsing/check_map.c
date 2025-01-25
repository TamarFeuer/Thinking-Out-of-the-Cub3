#include "../inc/game.h"

bool	check_map_validity(t_data *data);
bool	is_surrounded_by_walls(t_data *data, char **map);
bool	check_col_above(char **map, int row, int col);
bool	check_col_below(t_data *data, char **map, int row, int col);

/**
 * The map must be surrounded by walls.
 * 
 * There can be spaces, but parsing has to make sure that there are no gaps without walls.
 * And if the spaces are within the map, those too have to be surrounded by walls.
 */

bool	check_map_validity(t_data *data)
{
	if (!data->map_data.map)
	{
		printf("%s\n", ERR_NULL_MAP);
		return (false);
	}
	data->map_data.map_rows = 0;
	while (data->map_data.map[data->map_data.map_rows] != NULL)
		data->map_data.map_rows++;
	is_surrounded_by_walls(data, data->map_data.map);
	//Check for invalid elements
	//Check for repeated cardinal elements

	// Check first line
	// Check second line (there has to be 1s or spaces where there are spaces in the 1st line)
	// Check third line (there has to be 1s or spaces where there are spaces in the 2nd and 1st line)
	// ...
	return (true);
}

bool	is_surrounded_by_walls(t_data *data, char **map)
{
	int	row;
	int	col;

	(void) data;
	if (!map)
		return (false);
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (row == 0 && map[row][col] == '0')
			{
				printf("ROW #%i doesn't have a wall where it should.\n", row);
				return (false);
			}
			if (row != 0 && map[row][col] == '0')
			{
				// if (!check_col_above(map, row, col))
				// 	return (false);
				if (!check_col_below(data, map, row, col))
					return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}

bool	check_col_above(char **map, int row, int col)
{
	if (!map || !*map)
	{
		printf("NULL MAP!\n");
		return (false);
	}
	if (row - 1 < 0)
	{
		printf("The map is not surrounded by walls.\n");
		return (false);
	}
	else if (row - 1 >= 0 && (map[row - 1][col] == '0' || map[row - 1][col] == ' '))
	{
		// printf("Checking the row above line #%i\n", row);
		return (check_col_above(map, row - 1, col));
	}
	else if (row - 1 >= 0 && map[row - 1][col] == '1')
		return (true);
	return (false);
}

bool	check_col_below(t_data *data, char **map, int row, int col)
{
	if (!map || !*map)
	{
		printf("NULL MAP!\n");
		return (false);
	}
	if (row + 1 >= data->map_data.map_rows)
	{
		printf("The map didn't have a wall where it should, and it ran out of lines.\n");
		return (false);
	}
	else if (row + 1 < data->map_data.map_rows && (map[row + 1][col] == '0' || map[row + 1][col] == ' '))
		return (check_col_below(data, map, row + 1, col));
	else if (row + 1 < data->map_data.map_rows && map[row + 1][col] == '1')
		return (true);
	return (false);
}




/** SKETCH Y
 * First and last lines, apart from spaces, have to contain '1's only.
 * 
 * 
 */


/** SKETCH Z
 * Create a helper function that checks the character below
 * 
 * If the character in question is ON THE EDGE (yet another helper function)
 * If it is a space, the character below can be either a space or a 1.
 * If it is a 0 it's invalid.
 * If it is a 1, it's surrounded by walls.
 * 
 * If it is NOT ON THE EDGE
 * If it is a 1, then it's a wall inside the map.
 * If it is a 0, then it surely must be surrounded by valid characters.
 * If that 0 is surrounded by spaces, then how do I determine that it's surrounded by walls?
 * 
 * //Create another that checks the character above?
 */







