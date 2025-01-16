#include "../inc/game.h"

static void	get_identifier(t_data *data, int *i, int *j);

void parse_identifiers(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->map_data.file_data;
	i = 0;
	j = 0;
	while (map[i][j]) //Skips empty lines and whitespaces
	{
		while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n'))
			j++;
		if (map[i][j] != '\0')
			break ;
		else
		{
			j = 0;
			i++;
		}
	}
	get_identifier(data, &i, &j);


	//skip empty lines
	//skip spaces
	//look for a valid identifier
	//look that it is not repeated
	//check that the file format is okay (it is a path, it's not a dir and it opens the file)
	//check that it's a valid texture?
	//check that there's no data after the path (only spaces or a new line character)
	//check that all 6 of the identifiers are present
}

static void	get_identifier(t_data *data, int *i, int *j)
{
	char	**map;

	map = data->map_data.file_data;
	if (map[*i][*j] == 'N' && map[*i][*j + 1] == 'O')
	{
		if (data->textures.north)
			printf("%s\n", ERR_TXT_REP); // & exit
		else
			get_texture_path(data, i, j);
			printf("OK\n");
			//skip spaces
			//dup the path, making sure malloc didn't fail
			//make sure there's nothing after the path
	}
	else if (map[*i][*j] == 'S' && map[*i][*j + 1] == 'O')
	{
		if (data->textures.south)
			printf("%s\n", ERR_TXT_REP); // & exit
	}
	else if (map[*i][*j] == 'W' && map[*i][*j + 1] == 'E')
	{
		if (data->textures.west)
			printf("%s\n", ERR_TXT_REP); // & exit
	}
	else if (map[*i][*j] == 'E' && map[*i][*j + 1] == 'A')
	{
		if (data->textures.east)
			printf("%s\n", ERR_TXT_REP); // & exit
	}
	else
		printf("%s\n", ERR_INV_TXT); // & exit
}

static void	get_texture_path(t_data *data, int *i, int *j)
{
	
}











// static void parse_map(t_data *data)
// {
// 	//skip empty lines
// 	//check at what line the map starts?
// 	//Count the number of lines in the map
// 	//Look for the longest line
// 	//Allocate memory for the map
// 	//Every space is an empty tile? Every tab is 4 empty tiles?
// 	//The order of the spaces should be preserved, but a line can be filled with spaces at the end
// 	//Apart from the spaces, the map has 3 characters: 0, 1 and N/E/W/S, with having a unique cardinal identifier.
// 	//It has to be surrounded by walls
// }
