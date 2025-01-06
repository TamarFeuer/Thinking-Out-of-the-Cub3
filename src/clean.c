#include "../inc/game.h"

void	clean_nicely(t_game *game)
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
		if (game->stats)
		{
			free (game->stats);
			game->stats = NULL;
		}
		free (game);
		game = NULL;
	}
		
}