/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexer.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:28:59 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/19 17:11:58 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "lexer.h"

void	del_token(void *token)
{
	free(((struct s_token *)token)->value);
	free(token);
}

static struct s_token	create_token(enum e_category category, char *lexeme,
		int line, char *log)
{
	struct s_token *const	new_token = malloc(sizeof(struct s_token));
	char *const				value = ft_strdup(lexeme);

	if (new_token && value)
	{
		new_token->name = category;
		new_token->value = value;
		new_token->line = line;
	}
	else
	{
		free(new_token);
		free(value);
		new_token = NULL;
		ft_strlcpy(log, "Out of memory", 64);
	}
	return (new_token);
}

static struct s_token	*evaluator(char *lexeme, int line, char *log)
{
	if (!ft_strncmp(lexeme, ",", 2))
		return (create_token(SEPARATOR, lexeme, line, log));
	if (!ft_strncmp(lexeme, "NO", 3) || !ft_strncmp(lexeme, "SO", 3)
		|| !ft_strncmp(lexeme, "WE", 3) || !ft_strncmp(lexeme, "EA", 3)
		|| !ft_strncmp(lexeme, "F", 2) || !ft_strncmp(lexeme, "C", 2))
		return (create_token(IDENTIFIER, lexeme, line, log));
	return (create_token(LITERAL, lexeme, line, log));
}

static void	scanner(int fd, char *log, t_list **ptokens)
{
	char			*line;
	struct s_token	*new_token;
	list_t			*new_link;
	int				nlines;

	nlines = 0;
	while (!*log && ft_getnextline_fd(&line, fd))
	{
		new_token = evaluator(ft_strtok(line, " \n"), nlines, log);
		while (new_token)
		{
			new_link = ft_lstnew(new_token);
			if (!new_link)
			{
				del_token(new_token);
				ft_strlcpy(log, "Out of memory", 64);
				return ;
			}
			ft_lstadd_back(tokens, new_link);
			new_token = evaluator(ft_strtok(NULL, " \n"), nlines, log);
		}
		nlines++;
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
		ft_lstclear(data->tokens, del_token);
		ft_getnextline(NULL, fd);
		clean_nicely(game, log);
	}
}
