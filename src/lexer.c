/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexer.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:28:59 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/22 18:40:21 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer_parser.h"

// https://en.wikipedia.org/wiki/Lexical_analysis

void	del_token(void *token)
{
	free(((struct s_token *)token)->value);
	free(token);
}

static void	evaluator(char *log, struct s_token *token, char *lexeme,
		size_t len)
{
	token->value = ft_substr(lexeme, 0, len);
	if (!token->value)
		return ((void)ft_strlcpy(log, "Out of memory", 64));
	if (!ft_strncmp(token->value, "NO", -1))
		token->id = NO;
	else if (!ft_strncmp(token->value, "SO", -1))
		token->id = SO;
	else if (!ft_strncmp(token->value, "WE", -1))
		token->id = WE;
	else if (!ft_strncmp(token->value, "EA", -1))
		token->id = EA;
	else if (!ft_strncmp(token->value, "F", -1))
		token->id = F;
	else if (!ft_strncmp(token->value, "C", -1))
		token->id = C;
	else if (!ft_strncmp(token->value, ",", -1))
		token->name = SEPARATOR;
	else
	{
		token->name = LITERAL;
		if (ft_strspn(token->value, "0123456789") == len)
			token->lflags |= TVALID_NUM;
		if (ft_strspn(token->value, "01NESW") == len)
			token->lflags |= TVALID_MAP;
	}
}

static int	create_token(char *log, t_list **ptokens, unsigned int line,
		unsigned int pos)
{
	struct s_token *const	new_token = malloc(sizeof(struct s_token));
	list_t *const			new_link = ft_lstnew(new_token);

	if (new_token && new_link)
	{
		token->name = IDENTIFIER;
		new_token->line = line;
		new_token->pos = pos;
		new_token->lflags = 0;
		ft_lstadd_back(ptokens, new_link);
		return (0);
	}
	free(new_token);
	free(new_link);
	ft_strlcpy(log, "Out of memory", 64);
	return (1);
}

static void	scanner(int fd, char *log, t_list **ptokens)
{
	char	*line;
	char	*lexemes;
	int		nlines;
	size_t	token_length;

	nlines = 0;
	while (!*log && ft_getnextline_fd(&line, fd))
	{
		lexemes = ft_strtok(line, " \t\n");
		while (lexemes && !*log && !create_token(log, ptokens, nlines,
				lexemes - line))
		{
			if (*lexemes == ',')
				token_length = 1;
			else
				token_length = ft_strcspn(lexemes, ",");
			evaluator(log, *ptokens, lexemes, token_length);
			lexemes += token_length;
			if (!*lexemes)
				lexemes = ft_strtok(NULL, " \t\n");
		}
		nlines++;
		free(line);
	}
}

void	lexer(t_game *game)
{
	t_data *const	data = game->data;
	const int		fd = open(data->cub_file, O_RDONLY);
	char			log[64];

	log[0] = '\0';
	data->tokens = NULL;
	if (fd < 0)
		ft_snprintf(log, 64, "Unable to open `%s\'", data->cub_file);
	scanner(fd, log, &data->tokens);
	if (fd >= 0 && close(fd) < 0 && !*log)
		ft_snprintf(log, 64, "Unable to close `%s\'", data->cub_file);
	if (*log)
	{
		ft_getnextline(NULL, fd);
		clean_nicely(game, log);
	}
}
