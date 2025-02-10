#include "../../inc/game.h"

static void	get_identifier(t_data *data, int *i, int *j);
char		*get_identifier_path(t_data *data, int *i, int *j);
static void	get_texture_path(t_data *data, t_pos_id id, int *i, int *j);
static void parse_color_identifiers(t_data *data);
u_int32_t	get_color(char *color);
bool		verify_identifiers(t_data *data);

# define RED 0
# define GREEN 1
# define BLUE 2
# define ALPHA 3

// Definitions

//New version
void parse_identifiers(t_data *data, int *i, int *j)
{
	char	**map;

	map = data->map_data.file_data;
	if (!map || !*map)
		return ;
	data->identifiers = (char **) ft_calloc(7, sizeof(char *)); // 6 identifiers + 1 NULL
	if (!data->identifiers)
	{
		printf("Malloc error at parse_identifiers\n");
		return ;
	}
	while (map && map[*i] && map[*i][*j]) //Skips empty lines and whitespaces
	{
		skip_whitespaces(map, *i, j);
		if (map[*i][*j] && map[*i][*j] != '\n')
			get_identifier(data, i, j);
		*j = 0;
		*i += 1;
		if (verify_identifiers(data))
			break ;
	}
	parse_color_identifiers(data);
	//check that it's a valid texture?
}

bool	verify_identifiers(t_data *data)
{
	int	i;

	i = 0;
	printf("verify_identifiers: %s\n", data->identifiers[i]);
	while (data->identifiers[i] != NULL)
	{
		printf("verify_identifiers %i\n", i);
		if (i == 5)
			return (true);
		i++;
	}
	return (false);
}

static void	get_identifier(t_data *data, int *i, int *j)
{
	char	**file;
	char	*identifier;

	file = data->map_data.file_data;
	skip_whitespaces(file, *i, j);
	identifier = &file[*i][*j];
	printf("get_identifier: %s\n", &file[*i][*j]);
	if (!ft_strncmp(identifier, "NO", 2)) // If there are so many if conditions here, is there a need for a function that identifies the identifiers?
		get_texture_path(data, NORTH_ID, i, j);
	else if (!ft_strncmp(identifier, "SO", 2))
		get_texture_path(data, SOUTH_ID, i, j);
	else if (!ft_strncmp(identifier, "EA", 2))
		get_texture_path(data, EAST_ID, i, j);
	else if (!ft_strncmp(identifier, "WE", 2))
		get_texture_path(data, WEST_ID, i, j);
	else if (!ft_strncmp(identifier, "F", 1))
		get_texture_path(data, FLOOR_ID, i, j);
	else if (!ft_strncmp(identifier, "C", 1))
		get_texture_path(data, CEILING_ID, i, j);
}

static void	get_texture_path(t_data *data, t_pos_id id, int *i, int *j)
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
		data->identifiers[id] = (char *) malloc(len + 1);
		if (!data->identifiers[id])
			printf("%s\n", ERR_MEM_ALL);
		k = 0;
		while (k < len)
		{
			data->identifiers[id][k++] = map[*i][*j];
			*j += 1;
		}
		data->identifiers[id][k] = '\0';
	}
	while (map[*i][*j] && (map[*i][*j] == ' ' || map[*i][*j] == '\t')) //Check for spaces after the filepath
		*j += 1;
	if (map[*i][*j] != '\n' && map[*i][*j] != '\0') //After the filepath and spaces there can only be a newline or a null terminator 
		printf("%s\n", ERR_IDE_OVL);
	printf("in get_texture_path: %s\n", data->identifiers[id]);
}

static void parse_color_identifiers(t_data *data)
{
	char	*floor;
	char	*ceiling;

	floor = data->identifiers[FLOOR_ID];
	ceiling = data->identifiers[CEILING_ID];
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
