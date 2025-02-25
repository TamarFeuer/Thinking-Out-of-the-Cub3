/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/22 12:39:26 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/25 16:04:37 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer_parser.h"

static void	check_for_parameters(char *log, t_data *data)
{
	if (!data->map_data.texture_files[E])
		return ((void)ft_strlcpy(log, "Missing EA element", 64));
	if (!data->map_data.texture_files[N])
		return ((void)ft_strlcpy(log, "Missing NO element", 64));
	if (!data->map_data.texture_files[W])
		return ((void)ft_strlcpy(log, "Missing WE element", 64));
	if (!data->map_data.texture_files[S])
		return ((void)ft_strlcpy(log, "Missing SO element", 64));
	if (*data->colors[FL] == -1)
		return ((void)ft_strlcpy(log, "Missing F element", 64));
	if (*data->colors[CE] == -1)
		return ((void)ft_strlcpy(log, "Missing C element", 64));
	if (!data->map_tokens)
		return ((void)ft_strlcpy(log, "Missing map element", 64));
}

static void	read_rgb(char *log, t_data *data, enum e_horizon horizon,
		t_list **plist)
{
	struct token_s	token;
	enum e_rgb		c;

	token = (*plist)->content;
	if (data->parsed[horizon] != -1)
		return ((void)ft_snprintf(log, 64, "(%d-%d) Duplicated %s identifer",
				token->line, token->pos, token->value));
	c = RED;
	while (!*log && c <= BLUE)
	{
		(*plist) = (*plist)->next;
		token = (*plist)->content;
		if (!(token->name == LITERAL && token->lflags & TVALID_NUM))
			return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\'. Expected a non-"
					"negative decimal", token->line, token->pos, token->value));
		if (atoi2(&data->parsed[horizon], token->value))
			return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\'. Exceeds the 255 "
					"limit", token->line, token->pos, token->value));
		(*plist) = (*plist)->next;
		token = (*plist)->content;
		if (token->name != SEPARATOR)
			return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\'. Expected a `,\'",
					token->line, token->pos, token->value));
		map_data->bgra[horizon] |= data->parsed[horizon] << 8 * (c++ - RED + 1);
	}
}

static void	get_identifier(char *log, t_data *data, t_list **plist)
{
	struct token_s *const	token = (*plist)->content;

	if (token->id == EA || token->id == NO || token->id == WE
		|| token->id == SO)
	{
		if (data->map_data.texture_files[token->id])
			return ((void)ft_snprintf(log, 64, "(%d-%d) Duplicated %s "
					"identifier", token->line, token->pos, token->value));
		if (!(*plist)->next || ((struct s_token *)(*plist)->next)->name
				!= LITERAL)
			return ((void)ft_snprintf(log, 64, "(%d-%d) Missing %s texture "
					"file", token->line, token->pos, token->value));
		*plist = (*plist)->next;
		data->map_data.texture_files[token->id]
			= ((struct s_token *)*plist)->value;
	}
	else if (token->id == F)
		read_rgb(log, data, FL, plist);
	else
		read_rgb(log, data, CE, plist);
}

static void	syntax_analysis(char *log, t_data *data)
{
	t_list			*current;
	struct token_s	*token;

	current = data->tokens;
	while (!*log && current && !syntax_error)
	{
		token = current->content;
		if (token->name == IDENTIFIER && !data->map_tokens)
			get_identifier(log, data, &current);
		else if (token->name == LITERAL && token->lflags & TVALID_MAP)
		{
			if (!data->map_tokens)
			{
				data->map_tokens = current;
				data->map_data.rows = token->line;
			}
		}
		else
			ft_snprintf(log, 64, "(%d-%d) Unexpected token `%s\'",
				token->line, token->pos, token->value);
		current = current->next;
	}
}

void	parser(t_game *game)
{
	t_data *const	data = game->data;
	char			log[64];

	data->parsed[FL] = -1;
	data->parsed[CE] = -1;
	data->map_tokens = NULL;
	data->map_data.bgra[FL] = 0xFF;
	data->map_data.bgra[CE] = 0xFF;
	data->map_data.texture_files[E] = NULL;
	data->map_data.texture_files[N] = NULL;
	data->map_data.texture_files[W] = NULL;
	data->map_data.texture_files[S] = NULL;
	syntax_analysis(log, data);
	if (!*log)
		check_for_parameters(log, data);
	data->parsed[0] = -1;
	data->parsed[1] = -1;
	if (!*log)
		build_map(log, game);
	if (*log)
		clean_nicely(game, log);
}
