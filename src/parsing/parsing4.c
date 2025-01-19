#include "../../inc/game.h"

void parse_map(t_data *data, int *i, int *j)
{
	char	**map;
	int		len;
	int		k;
	int		l;

	data->map_data.map = (char **) malloc(sizeof(char *) * (data->map_data.nbr_of_lines - *i + 1));
	if (!data->map_data.map)
		printf("%s\n", ERR_MEM_ALL);

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
	
	k = 0;
	while (map[*i] && map[*i][*j])
	{
		while (map[*i][*j] == ' ' || map[*i][*j] == '\t') //Skip spaces function?
			*j += 1;
		l = *j;
		len = 0;
		// while (map[*i][len] != ' ' && map[*i][len] != '\t' && map[*i][len] != '\n') // len being == *j
		while (map[*i][l] != '\0' && map[*i][l] != '\n')
		{
			if (!ft_isdigit(map[*i][l]) && !ft_is_pos_identifier(map[*i][l]) && map[*i][l] != ' ' && map[*i][l] != '\t') //later check that the pos identifier is not repeated?
				printf("There's an element in the map that's not valid.\n");
			else if (map[*i][l] != ' ' && map[*i][l] != '\t')
				len++;
			l++;
		}

		data->map_data.map[k] = (char *) malloc(len + 1);
		if (!data->map_data.map[k])
			printf("%s\n", ERR_MEM_ALL);

		l = 0;
		while (map[*i][*j] != '\0' && map[*i][*j] != '\n')
		{
			if (!ft_isdigit(map[*i][*j]) && !ft_is_pos_identifier(map[*i][*j]) && map[*i][*j] != ' ' && map[*i][*j] != '\t')
				printf("There's an element in the map that's not a digit: %c.\n", map[k][*j]);
			else if (map[*i][*j] != ' ' && map[*i][*j] != '\t')
				data->map_data.map[k][l] = map[*i][*j];
			else if (map[*i][*j] == ' ' || map[*i][*j] == '\t')
			{
				*j += 1;
				continue ;
			}
			*j += 1;
			l++;
		}
		data->map_data.map[k][l] = '\0';
		printf("Nbr of lines: %i\n", data->map_data.nbr_of_lines);
		printf("i: %i\n", *i);
		printf("MAP[%i]: %s\n", k, data->map_data.map[k]);
		k++;
		*i += 1;
		*j = 0;
	}
	data->map_data.map[k] = NULL;
}
