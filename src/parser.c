/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/22 12:39:26 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/28 17:18:27 by rtorrent       ########   odam.nl        */
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
	if (data->parsed[FL] == -1)
		return ((void)ft_strlcpy(log, "Missing F element", 64));
	if (data->parsed[CE] == -1)
		return ((void)ft_strlcpy(log, "Missing C element", 64));
	if (!data->map_tokens)
		return ((void)ft_strlcpy(log, "Missing map element", 64));
}

static void	read_rgb(char *log, t_data *data, enum e_horizon hrzn,
		t_list **plist)
{
	struct s_token	*token;
	enum e_rgb		c;

	c = RED;
	while (!*log && c <= BLUE)
	{
		(*plist) = (*plist)->next;
		token = (*plist)->content;
		if (!(token->name == LITERAL && token->lflags & TVALID_NUM))
			return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\'. Expected a non-"
					"negative decimal", token->line, token->pos, token->value));
		if (atoi2(&data->parsed[hrzn], token->value))
			return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\'. Exceeds the 255 "
					"limit", token->line, token->pos, token->value));
		if (c < BLUE)
		{
			(*plist) = (*plist)->next;
			token = (*plist)->content;
			if (token->name != SEPARATOR)
				return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\'. Expected a "
						"`,\'", token->line, token->pos, token->value));
		}
		data->map_data.rgba[hrzn] |= data->parsed[hrzn] << 8 * (3 - c++);
	}
}

static void	get_identifier(char *log, t_data *data, t_list **plist)
{
	struct s_token *const	token = (*plist)->content;

	if (token->id == EA || token->id == NO || token->id == WE
		|| token->id == SO)
	{
		if (data->map_data.texture_files[token->id])
			return ((void)ft_snprintf(log, 64, "(%d-%d) Duplicated %s "
					"identifier", token->line, token->pos, token->value));
		if (!(*plist)->next || ((struct s_token *)(*plist)->next->content)->name
				!= LITERAL)
			return ((void)ft_snprintf(log, 64, "(%d-%d) Missing %s texture "
					"file", token->line, token->pos, token->value));
		*plist = (*plist)->next;
		data->map_data.texture_files[token->id]
			= ((struct s_token *)(*plist)->content)->value;
	}
	else if (token->id == F && data->parsed[FL] == -1)
		read_rgb(log, data, FL, plist);
	else if (token->id == C && data->parsed[CE] == -1)
		read_rgb(log, data, CE, plist);
	else
		return ((void)ft_snprintf(log, 64, "(%d-%d) Duplicated %s identifer",
				token->line, token->pos, token->value));
}

static void	syntax_analysis(char *log, t_data *data)
{
	t_list			*current;
	struct s_token	*token;

	current = data->tokens;
	while (!*log && current)
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

	log[0] = '\0';
	data->parsed[FL] = -1;
	data->parsed[CE] = -1;
	data->map_tokens = NULL;
	data->map_data.rgba[FL] = 0xFF;
	data->map_data.rgba[CE] = 0xFF;
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
