#include "../inc/game.h"

void print_stats(t_game *game)
{
	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);

	char *temp = ft_ftoa(game->player.angle / M_PI, 6);
	if (!temp)
		printf("error converting float to string\n");
	char *str = ft_strjoin ("Angle: ", temp);
	free (temp);
	if (!str)
		printf("error allocation dynamic memory\n");	
	str = ft_strjoin (str, "PI");
	if (!str)
		printf("error allocation dynamic memory\n");
	str = ft_strjoin (str, " X: ");
	if (!str)
		printf("error allocation dynamic memory\n");
	temp = ft_itoa((game->player.x - X_START)/CONST);
	// temp = ft_itoa((game->player.x - X_START));
	if (!temp)
		printf("error converting float to string\n");
	str = ft_strjoin (str, temp);
	free(temp);
	if (!str)
		printf("error allocation dynamic memory\n");
	str = ft_strjoin (str, " Y: ");
	if (!str)
		printf("error allocation dynamic memory\n");
	
	temp = ft_itoa((game->player.y - Y_START)/CONST);
	// temp = ft_itoa((game->player.y - Y_START) );
	if (!temp)
		printf("error converting float to string\n");
	str = ft_strjoin (str, temp);
	free(temp);
	if (!str)
		printf("error allocation dynamic memory\n");
	game->stats = mlx_put_string(game->mlx, str, X_START, Y_START/2);

	free (str);
	if (!game->stats)
		printf("error putting string on screen\n");
}