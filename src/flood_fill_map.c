/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   flood_fill_map.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/25 16:18:16 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/25 16:52:28 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static	flood_fill(struct s_mapdata *mdata, char *map, t_point *point)
{
}

void    flood_fill_map(t_game *game)
{
	char *const	dup_map = ft_strdup(game->data->map);

	if (!dup_map)
		clean_nicely(game, "Out of memory");
	flood_fill(game, game->data->

	free(dup_map);
}
