#include "../inc/game.h"

static void	delete_mlx(t_game *game)
{
	enum e_dir	dir;

	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);
	if (game->scene)
		mlx_delete_image(game->mlx, game->scene);
	dir = E;
	while (dir <= S)
	{
		if (game->textures[dir])
			mlx_delete_texture(game->textures[dir]);
		dir++;
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	clean_nicely(t_game *game, char *error_message)
{
	if (game)
	{
		if (game->data)
		{
			ft_lstclear(&game->data->tokens, del_token);
			free(game->data->map);
		}
		free(game->data);
		free(game->ray);
		delete_mlx(game);
		free(game);
	}
	if (error_message)
	{
		printf("Error\ncube3D: %s\n", error_message);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
