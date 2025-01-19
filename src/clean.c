#include "../inc/game.h"

void	delete_static_images(t_game *game)
{
	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);
	if (game->fill)
		mlx_delete_image(game->mlx, game->fill);
	if (game->scene)
		mlx_delete_image(game->mlx, game->scene);
	if (game->grid)
		mlx_delete_image(game->mlx, game->grid);
}

void	clean_nicely(t_game *game)  //use ft_free as in minishell
{
	//free_map_grid
	if (game)
	{
		// if (game->fd != -1)
		// 	close(game->fd);
		delete_static_images(game);
		printf ("amount of fill is %ld\n", game->fill->count);  //check why there are still instances
		
		if (game->mapdata)
		{
			free(game->mapdata);
			game->mapdata = NULL;
		}
		if (game->ray)
		{
			free(game->ray);
			game->ray = NULL;
		}
			mlx_terminate(game->mlx);
		free(game);
	}
}
 //add cleaning the wall textures