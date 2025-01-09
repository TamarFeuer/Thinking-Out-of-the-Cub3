#include "../inc/game.h"

void	clean_nicely(t_game *game)  //use ft_free as in minishell
{
	if (game)
	{
		if (game->map)
		{
			free (game->map);
			game->map = NULL;
		}
		if (game->map)
		{
			free (game->map);
			game->map = NULL;
		}
		if (game->player.player_img)
		{
			free (game->player.player_img);
			game->player.player_img = NULL;
		}
		if (game->player_dir)
		{
			free (game->player_dir);
			game->player_dir = NULL;
		}
		if (game->rays)
		{
			free (game->rays);
			game->rays = NULL;
		}
		if (game->stats)
		{
			free (game->stats);
			game->stats = NULL;
		}

		if (game->mapdata)
		{
			free (game->mapdata);
			game->mapdata = NULL;
		}
		free (game);
		game = NULL;
	}

	//free all instances of the roof tiles
}