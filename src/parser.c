/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/22 12:39:26 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/22 19:01:51 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer_parser.h"

static void	check_for_parameters(char *log, t_data *data)
{
	if (!data->texture_files[N])
		return ((void)ft_strlcpy(log, "Missing NO element", 64));
	if (!data->texture_files[S])
		return ((void)ft_strlcpy(log, "Missing SO element", 64));
	if (!data->texture_files[E])
		return ((void)ft_strlcpy(log, "Missing EA element", 64));
	if (!data->texture_files[W])
		return ((void)ft_strlcpy(log, "Missing WE element", 64));
	if (*data->colors[FL] == -1)
		return ((void)ft_strlcpy(log, "Missing F element", 64));
	if (*data->colors[CE] == -1)
		return ((void)ft_strlcpy(log, "Missing C element", 64));
	if (!data->map_tokens)
		return ((void)ft_strlcpy(log, "Missing map element", 64));
}

static void	get_rgb(char *log, t_data *data, enum e_horizon horizon,
		t_list **plist)
{
	struct token_s	token;
	enum e_rgb		c;

	token = (*plist)->content;
	if (*data->colors[horizon] != -1)
		return ((void)ft_snprintf(log, 64, "(%d-%d) Duplicated %s "
				"identifier", token->line, token->pos, token->value));
	c = RED;
	while (!*log && c <= BLUE)
	{
		(*plist) = (*plist)->next;
		token = (*plist)->content;
		if (!(token->name == LITERAL && token->lflags & TVALID_NUM))
			return ((void)ft_snprintf(log, 64, "(%d-%d) Non-numerical "
					"token `%s\'", token->line, token->pos, token->value));
		if (atoi2(&data->colors[horizon][c], token->value))
			return ((void)ft_snprintf(log, 64, "(%d-%d) `%s\' exceeds "
					"255 limit", token->line, token->pos, token->value));
		(*plist) = (*plist)->next;
		token = (*plist)->content;
		if (token->name != SEPARATOR)
			return ((void)ft_snprintf(log, 64, "(%d-%d) Unexpected token "
					"`%s\'", token->line, token->pos, token->value));
		c++;
	}
}

static void	get_identifier(char *log, t_data *data, t_list **plist)
{
	struct token_s *const	token = (*plist)->content;

	if ((token->id == NO || token->id == SO || token->id == EA
			|| token->id == WE))
	{
		if (data->texture_files[token->id])
			return ((void)ft_snprintf(log, 64, "(%d-%d) Duplicated %s\ "
					"identifier", token->line, token->pos, token->value));
		if (!(*plist)->next || ((struct s_token *)(*plist)->next)->name
				!= LITERAL)
			return ((void)ft_snprintf(log, 64, "(%d-%d) Missing %s "
					"texture file", token->line, token->pos, token->value));
		*plist = (*plist)->next;
		data->texture_files[token->id] = ((struct s_token *)*plist)->value;
	}
	else if (token->id == F)
		get_rgb(log, data, FL, plist);
	else
		get_rgb(log, data, CE, plist);
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
				data->map_tokens = current;
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

	data->texture_files[N] = NULL;
	data->texture_files[S] = NULL;
	data->texture_files[E] = NULL;
	data->texture_files[W] = NULL;
	*data->colors[FL] = -1;
	*data->colors[CE] = -1;
	data->map_tokens = NULL;
	syntax_analysis(log, data);
	if (!*log)
		check_for_parameters(log, data);
	if (!*log)
		build_map(log, data);
	if (*log)
		clean_nicely(game, log);
}
