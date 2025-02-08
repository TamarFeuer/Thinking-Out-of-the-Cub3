#include "../../inc/game.h"

# define RED 0
# define GREEN 1
# define BLUE 2
# define ALPHA 3

typedef enum e_pos_id
{
	INVAL_ID = 0,
	NORTH_ID,
	SOUTH_ID,
	EAST_ID,
	WEST_ID
} t_pos_id;

static void	get_identifier(t_data *data, int *i, int *j);
char		*get_identifier_path(t_data *data, int *i, int *j);
static void	get_texture_path(t_data *data, char **texture, int *i, int *j);
static void parse_color_identifiers(t_data *data);
u_int32_t	get_color(char *color);

t_pos_id identify_identifier(char *identifier)
{
	if (!ft_strncmp(identifier, "NO", 3))
		return (NORTH_ID);
	else if (!ft_strncmp(identifier, "SO", 3))
		return (SOUTH_ID);
	else if (!ft_strncmp(identifier, "EA", 3))
		return (EAST_ID);
	else if (!ft_strncmp(identifier, "WE", 3))
		return (WEST_ID);
	return (INVAL_ID);
}

//New version
void parse_identifiers(t_data *data, int *i, int *j)
{
	char	**map;

	map = data->map_data.file_data;
	ft_memset(&data->textures, 0, sizeof(t_identifiers));
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
	parse_color_identifiers(data);
	//check that it's a valid texture?
}

static void	get_identifier(t_data *data, int *i, int *j)
{
	char	**file;
	char	*identifier;

	file = data->map_data.file_data;
	ft_memset(&data->textures, 0, sizeof(t_identifiers));
	while (file[*i] && file[*i][*j]) //Skips empty lines and whitespaces
	{
		skip_whitespaces(file, *i, j);
		identifier = ft_strdup(&file[*i][*j]);
		if (!identifier)
		{
			printf("Malloc error in get_identifier\n");
			return ;
		}
		if (identify_identifier(identifier) == NORTH_ID)
			get_texture_path(data, &data->textures.north, i, j);
		else if (identify_identifier(identifier) == SOUTH_ID)
			data->textures.south = get_identifier_path(data, i, j);
		else if (identify_identifier(identifier) == EAST_ID)
			data->textures.east = get_identifier_path(data, i, j);
		else if (identify_identifier(identifier) == WEST_ID)
			data->textures.west = get_identifier_path(data, i, j);
		*j = 0;
		*i += 1;
		if (data->textures.north && data->textures.south && data->textures.east 
			&& data->textures.west && data->textures.ceiling && data->textures.floor)
			break ;
	}
	parse_color_identifiers(data);
}


char	*get_identifier_path(t_data *data, int *i, int *j)
{
	char	**file;
	char	*path;

	file = data->map_data.file_data;
	skip_whitespaces(file, *i, j);
	printf("get_identifier_path: %s\n", &file[*i][*j]);
	path = NULL;
	return (path);
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
}

static void parse_color_identifiers(t_data *data)
{
	char	*floor;
	char	*ceiling;

	floor = data->textures.floor;
	ceiling = data->textures.ceiling;
	data->map_data.floor_color = get_color(floor);
	data->map_data.ceiling_color = get_color(ceiling);
}

u_int32_t	get_color(char *color)
{
	u_int32_t	rgba = 0;
	char		**arr;
	u_int8_t	rgb[4];

	arr = ft_split(color, ',');
	if (!arr)
		return (0);
	rgb[RED] = ft_atoi_b16(arr[RED]);
	rgb[GREEN] = ft_atoi_b16(arr[GREEN]);
	rgb[BLUE] = ft_atoi_b16(arr[BLUE]);
	if (arr[ALPHA] == NULL)
		rgb[ALPHA] = 255;
	else
		rgb[ALPHA] = ft_atoi_b16(arr[ALPHA]);
	rgba = (rgb[RED] << 24) | (rgb[GREEN] << 16) | (rgb[BLUE] << 8) | rgb[ALPHA];
	ft_free_2d((void ***) &arr);
	return (rgba);
}
