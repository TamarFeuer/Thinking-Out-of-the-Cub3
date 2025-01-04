#ifndef GAME_H
# define GAME_H

#include "MLX42.h"


typedef struct s_pox
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_pos	player_pos;
}	t_game;

#endif