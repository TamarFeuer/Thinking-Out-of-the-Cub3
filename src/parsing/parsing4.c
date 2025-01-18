#include "../../inc/game.h"

void parse_map(t_data *data, int *i, int *j)
{
	char	**map;
	int		len;
	int		row;

	map = data->map_data.file_data;
	while (map[*i] && map[*i][*j]) //Skips empty lines and whitespaces
	{
		while (map[*i][*j] == ' ' || map[*i][*j] == '\t') //Skip spaces function?
			*j += 1;
		if (map[*i][*j] != '\n')
			break ;
		*j = 0;
		*i += 1;
	}
	if (!ft_isdigit(map[*i][*j]))
		printf("The map does not begin with a digit.\n");
	
	while (map[*i] && map[*i][*j])
	{
		while (map[*i][*j] == ' ' || map[*i][*j] == '\t') //Skip spaces function?
			*j += 1;
		len = *j;
		while (map[*i][len] != ' ' && map[*i][len] != '\t' && map[*i][len] != '\n')
		{
			if (!ft_isdigit(map[*i][len]))
				printf("There's an element in the map that's not a digit.\n");
			len++;
		}

	}
}
