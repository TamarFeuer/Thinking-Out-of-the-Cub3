/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   map_parser.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/24 13:12:32 by rtorrent       #+#    #+#                */
/*   Updated: 2025/03/04 11:53:28 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer_parser.h"

static void	check_for_player(char *log, t_game *game, struct s_token *token,
		size_t index)
{
	enum e_dir		direction;

	index += ft_strcspn(token->value + index, "NSEW");
	if (index == token->len)
		return ;
	if (game->player.angle_quad != -1)
	{
		ft_snprintf(log, LOG, "(%d-%d) Player starting position redefined",
			token->line, token->pos + index);
		clean_nicely(game, log);
	}
	game->player.p_pos.x = (double)(token->pos + index - game->data->parsed[0]);
	game->player.p_pos.y = (double)(token->line - game->data->parsed[1]);
	direction = E;
	if (token->value[index] == 'N')
		direction = N;
	else if (token->value[index] == 'W')
		direction = W;
	else if (token->value[index] == 'S')
		direction = S;
	game->player.angle = direction * M_PI / 2;
	game->player.angle_quad = direction + 1;
	token->value[index] = EMPTY;
	check_for_player(log, game, token, index + 1);
}

static void	assemble_map(char *log, t_game *game)
{
	t_data *const	data = game->data;
	t_list			*map_tokens;
	struct s_token	*token;
	size_t			index;

	map_tokens = data->map_tokens;
	while (map_tokens)
	{
		token = map_tokens->content;
		index = (token->line - data->parsed[1]) * data->map_data.cols
			+ token->pos - data->parsed[0];
		check_for_player(log, game, token, 0);
		ft_memcpy(data->map + index, token->value, token->len);
		map_tokens = map_tokens->next;
	}
}

static void	determine_dimensions(char *log, t_data *data,
		unsigned int last_line)
{
	t_list			*map_tokens;
	struct s_token	*token;

	data->map_data.rows = 1;
	map_tokens = data->map_tokens;
	while (map_tokens)
	{
		token = map_tokens->content;
		if (token->line > last_line + 1)
			return ((void)ft_snprintf(log, LOG, "Empty map row detected at "
					"line %d", ++last_line));
		if (token->line > last_line)
		{
			last_line++;
			data->map_data.rows++;
		}
		if (data->parsed[0] < 0 || token->pos < (unsigned int)data->parsed[0])
			data->parsed[0] = token->pos;
		if (data->parsed[1] < 0
			|| token->pos + token->len > (unsigned int)data->parsed[1])
			data->parsed[1] = token->pos + token->len;
		map_tokens = map_tokens->next;
	}
	data->map_data.cols = data->parsed[1] - data->parsed[0];
	data->parsed[1] = ((struct s_token *)data->map_tokens->content)->line;
}

void	build_map(char *log, t_game *game)
{
	t_data *const	data = game->data;
	size_t			map_size;

	determine_dimensions(log, data, data->map_data.rows);
	map_size = data->map_data.rows * data->map_data.cols;
	data->map = malloc(map_size + 1);
	if (!data->map)
		clean_nicely(game, "Out of memory");
	ft_memset(data->map, SPACE, map_size);
	data->map[map_size] = '\0';
	game->player.angle_quad = -1;
	assemble_map(log, game);
	if (game->player.angle_quad == -1)
		clean_nicely(game, "Missing player starting position");
}
