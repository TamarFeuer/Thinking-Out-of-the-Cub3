#include "../inc/game.h"

char *ft_strjoin_free(char *left, char *right, int free_flag)
{
	char *result = ft_strjoin(left, right);
	if (!result)
		return NULL;

	if (free_flag == 1 || free_flag == 3)
	{
		free(left);
		left = NULL;
	}
	if (free_flag == 2 || free_flag == 3)
	{
		free(right);
		right = NULL;
	}
	return result;
}

void print_stats(t_game *game)
{
	char *str;
	
	
	char *temp = ft_ftoa(game->player.angle / M_PI, 6);
	if (!temp)
		return;
	str = ft_strjoin("Angle: ", temp);
	free(temp);
	if (!str)
		return;
	str = ft_strjoin_free(str, "PI X: ", 1);
	temp = ft_itoa(((game->player.p_pos.x) - X_START) / CONST);  //if fails free stuff
	if (temp)
		str = ft_strjoin_free(str, temp, 1);
	str = ft_strjoin_free(str, " Y: ", 1);
	temp = ft_itoa(((game->player.p_pos.y) - Y_START) / CONST);  //if fails, free stuff
	if (temp)
		str = ft_strjoin_free(str, temp, 1);
	game->stats = mlx_put_string(game->mlx, str, 0, MMAP_HEIGHT);
	free(str);

}
