/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   map_parser.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/24 13:12:32 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/27 13:59:38 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer_parser.h"

static void	check_for_player(char *log, t_game *game, struct s_token *token,
		size_t start_index)
{
	const size_t	not_player = ft_strcspn(token->value + start_index, "NSEW");
	const size_t	index_not_player = start_index + not_player;
	enum e_dir		direction;

	if (index_not_player == token->len)
		return ;
	if (game->player.angle_quad != -1)
	{
		ft_snprintf(log, 64, "(%d-%d) Player starting position redefined",
			token->line, token->pos + index_not_player);
		clean_nicely(game, log);
	}
	game->player.p_pos.x = token->pos + index_not_player - game->player.p_pos.x;
	game->player.p_pos.y = token->line - game->player.p_pos.y;
	direction = E;
	if (token->value[index_not_player] == 'N')
		direction = N;
	else if (token->value[index_not_player] == 'W')
		direction = W;
	else if (token->value[index_not_player] == 'S')
		direction = S;
	game->player.angle = direction * M_PI / 2;
	game->player.angle_quad = direction + 1;
	token->value[index_not_player] = EMPTY;
	check_for_player(log, game, token, index_not_player + 1);
}

static void	assemble_map(char *log, t_game *game)
{
	t_list			*map_tokens;
	struct s_token	*token;
	unsigned int	first_line;
	size_t			index;

	map_tokens = game->data->map_tokens;
	first_line = ((struct s_token *)map_tokens->content)->line;
	while (map_tokens)
	{
		token = map_tokens->content;
		index = (token->line - first_line) * game->data->map_data.cols
			+ token->pos - game->data->parsed[0];
		check_for_player(log, game, token, 0);
		ft_strlcpy(game->data->map + index, token->value, -1);
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
			return ((void)ft_snprintf(log, 64, "Empty map row detected at line "
					"%d", ++last_line));
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
	game->player.p_pos.x = (double)data->parsed[0];
	game->player.p_pos.y
		= (double)((struct s_token *)data->map_tokens->content)->line;
	game->player.angle_quad = -1;
	assemble_map(log, game);
	if (game->player.angle_quad == -1)
		clean_nicely(game, "Missing player starting position");
}
