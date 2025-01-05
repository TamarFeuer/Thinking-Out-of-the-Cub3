#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>



typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player 
{
    int 		x;
    int 		y;
    float 		angle;  // in radians
	mlx_image_t	*player_img;
} t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	t_player	player;

}	t_game;

#endif