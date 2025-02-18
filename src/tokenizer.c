/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tokenizer.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:28:59 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/18 19:34:26 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "tokenizer.h"

static void clean_scanner(t_list **tokens)
{
	ft_getnextline(NULL, fd);
	ft_lstclear(tokens, free);
}

static void	scanner(t_list **tokens, int fd)
{
	char			*line;
	struct s_token	*new_token;
	list_t			*new_link;

	while (ft_getnextline_fd(&line, fd))
	{
		if (tokenization(&new_token, ft_strtok(line, " \n")) < 0)
			return clean_scanner(tokens);
		while (new_token)
		{
			new_link = ft_lstnew(new_token);
			if (!new_link)
			{
				free(new_token);
				return clean_scanner(tokens);
			}
			ft_lstadd_back(tokens, new_link);
			
	}
		
			
		
		
		
}

void	tokenizer(t_game *game)
{
	const int	fd = open(game->scene_file, O_RDONLY);
	char		log[64];
	t_list		*tokens;

	if (fd < 0)
	{
		ft_snprintf(log, 64, "Unable to open `%s\'", game->scene_file);
		clean_nicely(game, log);
	}
	tokens = scanner(fd);
	if (close(fd) < 0)
	{
		ft_snprintf(log, 64, "Unable to close `%s\'", game->scene_file);
		clean_nicely(game, log);
	}
}
