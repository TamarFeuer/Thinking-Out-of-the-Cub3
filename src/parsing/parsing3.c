#include "../../inc/game.h"

# define RED 0
# define GREEN 1
# define BLUE 2
# define ALPHA 250

static void	get_identifier(t_data *data, int *i, int *j);
static void	get_texture_path(t_data *data, char **texture, int *i, int *j);
static void parse_color_identifiers(t_data *data);
u_int32_t	get_color(char *color);

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
	// printf("PARSE IDENTIFIERS %s\n", &map[*i][*j]);
	//Could iterate this with an enum.
	// check_file_format(data->textures.north);
	// check_file_format(data->textures.south);
	// check_file_format(data->textures.east);
	// check_file_format(data->textures.west);
	parse_color_identifiers(data);
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
		// printf("NO\n");
		get_texture_path(data, &data->textures.north, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "SO", 2) == 0 && !data->textures.south)
	{
		// printf("SO\n");
		get_texture_path(data, &data->textures.south, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "WE", 2) == 0 && !data->textures.west)
	{
		// printf("WE\n");
		get_texture_path(data, &data->textures.west, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "EA", 2) == 0 && !data->textures.east)
	{
		// printf("EA\n");
		get_texture_path(data, &data->textures.east, i, j);
	}
	else if (ft_strncmp(&map[*i][*j], "F", 1) == 0 && !data->textures.floor)
	{
		// printf("F\n");
		get_texture_path(data, &data->textures.floor, i, j);
		// printf("FLOOR: %s\n", data->textures.floor);
	}
	else if (ft_strncmp(&map[*i][*j], "C", 1) == 0 && !data->textures.ceiling) //&& check there's nothing random right after the string
	{
		// printf("C\n");
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
	// printf("Texture: %s\n", *texture);
}

static void parse_color_identifiers(t_data *data)
{
	char	*floor;
	char	*ceiling;

	floor = data->textures.floor;
	ceiling = data->textures.ceiling;
	data->map_data.floor_color = get_color(floor);
	data->map_data.ceiling_color = get_color(ceiling);
	printf("FLOOR COLOUR, parse_color_identifiers: %d\n", data->map_data.floor_color);
	printf("CEILING COLOUR, parse_color_identifiers: %d\n", data->map_data.ceiling_color);
}

u_int32_t	get_color(char *color)
{
	u_int32_t	rgba = 0;
	char		**arr;
	u_int8_t	rgb[3];

	arr = ft_split(color, ',');
	if (!arr)
		return (0);
	rgb[RED] = ft_atoi(arr[RED]);
	rgb[GREEN] = ft_atoi(arr[GREEN]);
	rgb[BLUE] = ft_atoi(arr[BLUE]);
	ft_free_2d((void ***) &arr);
	printf("RED: %d\n", rgb[RED]);
	printf("GREEN: %d\n", rgb[GREEN]);
	printf("BLUE: %d\n", rgb[BLUE]);
	if (rgb[RED] > 255 || rgb[RED] < 0
		|| rgb[GREEN] > 255 || rgb[GREEN] < 0
		|| rgb[BLUE] > 255 || rgb[BLUE] < 0)
	{
		printf("Invalid colour values. get_colour\n");
		return (0);
	}
	rgba = (rgb[RED] << 24) | (rgb[GREEN] << 16) | (rgb[BLUE] << 8) | ALPHA;

	return (rgba);
}
