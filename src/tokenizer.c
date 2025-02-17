/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tokenizer.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:28:59 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/17 17:33:57 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	tokenizer(t_game *game)
{
	const int	fd = open(game->scene_file, O_RDONLY);
	char		log[64];

	if (fd < 0)
	{
		ft_snprintf(log, 64, "Unable to open `%s\'", game->scene_file);
		clean_nicely(game, log);
	}

// Scanner

	if (close(fd) < 0)
	{
		ft_snprintf(log, 64, "Unable to close `%s\'", game->scene_file);
		clean_nicely(game, log);
	}
}
