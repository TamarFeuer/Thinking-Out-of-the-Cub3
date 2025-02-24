/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   map_parser.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/24 13:12:32 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/24 20:06:22 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer_parser.h"

static void	assemble_map(char *log, t_data *data, t_player *player)
{
	t_list			*map_tokens;
	struct s_token	*token;
	int				first_line;
	int				index;

	map_tokens = data->map_tokens;
	first_line = ((struct s_token *)map_tokens->content)->line;
	while (map_tokens)
	{
		index = (token->line - first_line) * data->map_data.cols
			+ token->pos - data->parsed[0];
		ft_strlcpy(data->map + index, token->value, -1);
// TODO Player starting position
		map_tokens = map_tokens->next;
	}
}

static void	determine_dimensions(char *log, t_data *data)
{
	t_list			*map_tokens;
	struct s_token	*token;
	int				last_line;

	last_line = data->map_data.rows;
	data->map_data.rows = 1;
	map_tokens = data->map_tokens;
	while (map_tokens)
	{
		token = map_tokens->content;
		if (token->line > last_line + 1)
			return (ft_snprintf(log, 64, "Empty map row detected at line %d",
					++last_line));
		if (token->line > last_line)
		{
			last_line++;
			data->map_data.rows++;
		}
		if (data->parsed[0] < 0 || token->pos < data->parsed[0])
			data->parsed[0] = token->pos;
		if (data->parsed[1] < 0 || token->pos + token->len > data->parsed[1])
			data->parsed[1] = token->pos + len;
		map_tokens = map_tokens->next;
	}
	data->map_data.cols = data->parsed[1] - data->parsed[0];
}

void	build_map(char *log, t_game *game)
{
	t_data *const	data = game->data;
	size_t			map_size;

	determine_dimensions(log, data);
	map_size = data->map_data.rows * data->map_data.cols;
	data->map = malloc(map_size + 1);
	if (!data->map)
		clean_nicely(game, "Out of memory");
	ft_memset(data->map, SPACE, map_size);
	data->map[map_size] = '\0';
	game->player.angle_quad = -1;
	assemble_map(data, &game->player);
	if (game->player.angle_quad == -1)
		clean_nicely(game, "Missing player starting position");
}
