#include "../inc/game.h"

void draw_player(t_game *game)
{
	int size = PLAYER_SIZE * CONST; // Player is PLAYER_SIZE x PLAYER_SIZE pixels
	int x = round(game->player.x);
	int y = round(game->player.y);

	if (game->player.player_img)
		mlx_delete_image(game->mlx, game->player.player_img);

	game->player.player_img = mlx_new_image(game->mlx, size, size);
	if (!game->player.player_img)
	{
		printf("Failed to create player image.\n");
		return;
	}

	int i = 0;
	while (i < size)
	{
		int j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->player.player_img, i, j, 0xB00000FF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->player.player_img, x, y);
}