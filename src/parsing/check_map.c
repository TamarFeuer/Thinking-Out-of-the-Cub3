#include "../../inc/game.h"

t_ecode	check_map_validity(t_data *data);
t_ecode	has_repeated_elements(t_data *data);
bool	has_invalid_elements(t_data *data);


/**
 * The map must be surrounded by walls.
 * 
 * There can be spaces, but parsing has to make sure that there are no gaps without walls.
 * And if the spaces are within the map, those too have to be surrounded by walls.
 */

 t_ecode	check_map_validity(t_data *data)
{
	if (!data->map_data.map)
	{
		printf("%s\n", ERR_NULL_MAP);
		return (data->err_no = ECODE_NULL_MAP, ECODE_FAILURE);
	}
	data->map_data.rows = 0;
	while (data->map_data.map[data->map_data.rows] != NULL)
		data->map_data.rows++;
	is_surrounded_by_walls(data, data->map_data.map);
	// if (has_repeated_elements(data)) {
	// 	printf("Has repeated elements\n");
	// 	return (data->err_no = ECODE_REP_IDE, ECODE_FAILURE);
	// }
	// if (has_invalid_elements(data)) {
	// 	printf("Has invalid elements\n");
	// 	return (data->err_no = ECODE_INV_IDE, ECODE_FAILURE);
	// }	
	return (ECODE_SUCCESS);
}

bool	has_invalid_elements(t_data *data)
{
	char	**map;
	int		row;
	int		col;

	map = data->map_data.map;
	if (!map || !map[0])
		return (true);
	
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] != '0' && map[row][col] != '1'
				&& map[row][col] != 'E' && map[row][col] != 'W'
				&& map[row][col] != 'N' && map[row][col] != 'S'
				&& map[row][col] != ' ')
				return (true);
			col++;
		}
		row++;
	}
	return (false);
}

//Checks for repeated cardinal positions, but also if there's no cardinal pos too.
t_ecode	has_repeated_elements(t_data *data)
{
	char	**map;
	int		row;
	int		col;
	bool	has_pos;

	//Checks for map's NULLITY
	map = data->map_data.map;
	if (!map || !map[0])
	{
		printf("The map is null\n");
		return (data->err_no = ECODE_NULL_MAP, ECODE_FAILURE);
	}
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if ((map[row][col] == 'N' || map[row][col] == 'E'
				|| map[row][col] == 'W' || map[row][col] == 'S')
				&& has_pos == true)
				{
					printf("There are repeated cardinal positions\n");
					return (data->err_no = ECODE_REP_IDE, ECODE_FAILURE);
				}
			else if ((map[row][col] == 'N' || map[row][col] == 'E'
					|| map[row][col] == 'W' || map[row][col] == 'S')
					&& has_pos == false)
				has_pos = true;
			col++;
		}
		row++;
	}
	if (has_pos == false)
	{
		printf("There's no position\n");
		return (data->err_no = ECODE_NULL_MAP, ECODE_FAILURE);
	}
	return (ECODE_SUCCESS);
}
