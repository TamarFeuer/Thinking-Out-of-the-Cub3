#ifndef GAME_H
# define GAME_H

#include "MLX42.h"

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int		player_pos_x;
	int		player_pos_y;
}	t_game;

#endif