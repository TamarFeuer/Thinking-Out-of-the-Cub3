#include "../inc/game.h"

void	delete_images(t_game *game)
{
	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);
	if (game->scene)
		mlx_delete_image(game->mlx, game->scene);
}

//use ft_free as in minishell
void	clean_nicely(t_game *game, char *error_message)
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
		if (game->mlx)
		 	mlx_terminate(game->mlx); //causes seg fault??
		free(game->data);
		free(game->ray);
		free(game);
	}
	if (error_message)
	{
		printf("cube3D: %s\n", error_message);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
 //add cleaning the wall textures
