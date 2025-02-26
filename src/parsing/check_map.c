#include "../../inc/game.h"

bool	check_map_validity(t_game *game, t_data *data);
bool	has_repeated_elements(t_game *game, t_data *data);
bool	has_invalid_elements(t_game *game, t_data *data);


/**
 * The map must be surrounded by walls.
 * 
 * There can be spaces, but parsing has to make sure that there are no gaps without walls.
 * And if the spaces are within the map, those too have to be surrounded by walls.
 */

bool	check_map_validity(t_game *game, t_data *data)
{
	(void)data;
	if (!game->data->map_data.map)
	{
		printf("%s\n", ERR_NULL_MAP);
		return (false);
	}
	game->data->map_data.rows = 0;
	while (game->data->map_data.map[game->data->map_data.rows] != NULL)
		game->data->map_data.rows++;
	is_surrounded_by_walls(game->data, game->data->map_data.map);
	if (has_repeated_elements(game, game->data)) {
		printf("Has repeated elements\n");
		return (false);
	}
	if (has_invalid_elements(game, game->data)) {
		printf("Has invalid elements\n");
		return (false);
	}	
	return (true);
}

bool	has_invalid_elements(t_game *game, t_data *data)
{
	char	**map;
	int		row;
	int		col;

	(void)data;
	map = game->data->map_data.map;
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
bool	has_repeated_elements(t_game *game, t_data *data)
{
	char	**map;
	int		row;
	int		col;
	bool	has_pos;

	(void)data;
	//Checks for map's NULLITY
	map = game->data->map_data.map;
	if (!map || !map[0])
		return (true); //Doesn't have repeated elements, but it would segfault if not checked. So maybe throw a different error message.

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if ((map[row][col] == 'N' || map[row][col] == 'E' || map[row][col] == 'W' || map[row][col] == 'S') && has_pos == true) //How to refactor this?
				return (true);
			else if ((map[row][col] == 'N' || map[row][col] == 'E' || map[row][col] == 'W' || map[row][col] == 'S') && has_pos == false)
				has_pos = true;
			col++;
		}
		row++;
	}
	if (has_pos == false)
		return (true);
	return (false);
}
