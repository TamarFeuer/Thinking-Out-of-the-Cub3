#include "../../inc/game.h"

static void	get_identifier(t_data *data, int *i, int *j);
static void	get_texture_path(t_data *data, char **texture, int *i, int *j);
static void check_colour_texture(char *texture);

void parse_identifiers(t_data *data, int *i, int *j)
{
	char	**map;

	map = data->map_data.file_data;
	while (map[*i] && map[*i][*j]) //Skips empty lines and whitespaces
	{
		skip_whitespaces(map, *i, j);
		if (map[*i][*j] != '\n')
			get_identifier(data, i, j);
		*j = 0;
		*i += 1;
		if (data->textures.north && data->textures.south && data->textures.east \
			&& data->textures.west && data->textures.ceiling && data->textures.floor)
			break ;
	}

	//Could iterate this with an enum.
	// check_file_format(data->textures.north);
	// check_file_format(data->textures.south);
	// check_file_format(data->textures.east);
	// check_file_format(data->textures.west);
	check_colour_texture(data->textures.floor);
	check_colour_texture(data->textures.ceiling);
	//check that it's a valid texture?
}

//skip empty lines
	//skip spaces
	//look for a valid identifier
	//look that it is not repeated
	//check that there's no data after the path (only spaces or a new line character)
static void	get_identifier(t_data *data, int *i, int *j)
{
	char	**map;

	map = data->map_data.file_data;
	// if (map[*i][*j] == 'N' && map[*i][*j + 1] == 'O' && !data->textures.north)
	if (ft_strncmp(&map[*i][*j], "NO", 2) == 0 && !data->textures.north)
	{
		printf("NO\n");
		get_texture_path(data, &data->textures.north, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "SO", 2) == 0 && !data->textures.south)
	{
		printf("SO\n");
		get_texture_path(data, &data->textures.south, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "WE", 2) == 0 && !data->textures.west)
	{
		printf("WE\n");
		get_texture_path(data, &data->textures.west, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "EA", 2) == 0 && !data->textures.east)
	{
		printf("EA\n");
		get_texture_path(data, &data->textures.east, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "F", 1) == 0 && !data->textures.floor)
	{
		printf("F\n");
		get_texture_path(data, &data->textures.floor, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "C", 1) == 0 && !data->textures.ceiling) //&& check there's nothing random right after the string
	{
		printf("C\n");
		get_texture_path(data, &data->textures.ceiling, i, j);
	}
	else
	{
		printf("%s\n", ERR_INV_TXT); // & exit
		printf("The string is: %s.\n", &map[*i][*j]);
	}
}

static void	get_texture_path(t_data *data, char **texture, int *i, int *j)
{
	char	**map;
	int		len;
	int		k;

	map = data->map_data.file_data;
	*j += 2;
	skip_whitespaces(map, *i, j);
	if (map[*i][*j] == '\0' || map[*i][*j] == '\n')
		printf("%s\n", ERR_TXT_PATH);
	else
	{
		len = *j;
		while (map[*i][len] && map[*i][len] != ' ' && map[*i][len] != '\t' && map[*i][len] != '\n')
			len++;
		*texture = (char *) malloc(len - *j + 1);
		if (!*texture)
			printf("%s\n", ERR_MEM_ALL);
		k = 0;
		while (*j < len)
		{
			(*texture)[k++] = map[*i][*j];
			*j += 1;
		}
		(*texture)[k] = '\0';
	}
	while (map[*i][*j] && (map[*i][*j] == ' ' || map[*i][*j] == '\t')) //Check for spaces after the filepath
		*j += 1;
	if (map[*i][*j] != '\n' && map[*i][*j] != '\0') //After the filepath and spaces there can only be a newline or a null terminator 
		printf("%s\n", ERR_IDE_OVL);
}

static void check_colour_texture(char *texture)
{
	printf("The colour texture is: %s\n", texture);
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
