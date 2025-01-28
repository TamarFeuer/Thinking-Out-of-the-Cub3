#include "../inc/game.h"

void	delete_images(t_game *game)
{
	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);
	if (game->scene)
		mlx_delete_image(game->mlx, game->scene);
}

void	clean_nicely(t_game *game)  //use ft_free as in minishell
{
	//free_map_grid
	if (game)
	{
		// if (game->fd != -1)
		// 	close(game->fd);
		delete_images(game);
		
		if (game->mapdata)
		{
			free(game->mapdata);
			game->mapdata = NULL;
		}
		// if (game->mlx)
		// 	mlx_terminate(game->mlx); //causes seg fault??
		free(game);
	}
}
 //add cleaning the wall textures