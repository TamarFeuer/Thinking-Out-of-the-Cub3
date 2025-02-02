#include "../../inc/game.h"

static void	get_identifier(t_data *data, int *i, int *j);
static void	get_texture_path(t_data *data, char **texture, int *i, int *j);
static void parse_colour_identifiers(t_data *data);
int8_t	get_colour(char *colour);

void parse_identifiers(t_data *data, int *i, int *j)
{
	char	**map;

	map = data->map_data.file_data;
	ft_memset(&data->textures, 0, sizeof(t_textures));
	while (map[*i] && map[*i][*j]) //Skips empty lines and whitespaces
	{
		skip_whitespaces(map, *i, j);
		if (map[*i][*j] != '\n')
			get_identifier(data, i, j);
		*j = 0;
		*i += 1;
		if (data->textures.north && data->textures.south && data->textures.east 
			&& data->textures.west && data->textures.ceiling && data->textures.floor)
			break ;
	}
	printf("PARSE IDENTIFIERS %s\n", &map[*i][*j]);
	//Could iterate this with an enum.
	// check_file_format(data->textures.north);
	// check_file_format(data->textures.south);
	// check_file_format(data->textures.east);
	// check_file_format(data->textures.west);
	parse_colour_identifiers(data);
	// parse_colour_texture(data->textures.ceiling);
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
		// printf("FLOOR: %s\n", data->textures.floor);
	}
	else if (ft_strncmp(&map[*i][*j], "C", 1) == 0 && !data->textures.ceiling) //&& check there's nothing random right after the string
	{
		printf("C: \n");
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
	// printf("In get_texture_path, we're left with %s\n", &map[*i][*j]);
	if (map[*i][*j] == '\0' || map[*i][*j] == '\n')
		printf("%s\n", ERR_TXT_PATH);
	else
	{
		// printf("Row: %s\n", &map[*i][*j]);
		// while (map[*i][*j] && map[*i][*j] != ' ' && map[*i][*j] != '\t' && map[*i][*j] != '\n')
		// 	*j += 1;
		len = ft_strlen(&map[*i][*j]);
		*texture = (char *) malloc(len + 1);
		if (!*texture)
			printf("%s\n", ERR_MEM_ALL);
		k = 0;
		while (k < len)
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
	printf("Texture: %s\n", *texture);
}

static void parse_colour_identifiers(t_data *data)
{
	char	*floor;
	char	*ceiling;

	floor = data->textures.floor;
	ceiling = data->textures.ceiling;

	printf("FLOOR: %s\n", floor);
	printf("CEILING: %s\n", ceiling);

	data->map_data.floor_colour = get_colour(floor);
	data->map_data.ceiling_colour = get_colour(ceiling);
}

int8_t	get_colour(char *colour)
{
	// int8_t	rgba;
	char	**arr;
	// (void) colour;
	printf("%s\n", colour);

	arr = ft_split(colour, ',');
	printf("printing array now\n");
	ft_print_arr(arr);
	return 0;
}