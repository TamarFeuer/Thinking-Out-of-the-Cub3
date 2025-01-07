#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

//mini map
#define X_START 50
#define Y_START 50

#define CONST 6
#define ROWS 8
#define COLS 10
#define PIXELS_PER_BLOCK 8
#define PLAYER_SIZE 1

#define FOV 60.0 // Field of View in degrees
#define RAY_COUNT 120
#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)

#define MAX_RAY_LENGTH 300
#define MAP_WIDTH COLS * PIXELS_PER_BLOCK * CONST
#define MAP_HEIGHT ROWS * PIXELS_PER_BLOCK * CONST
#define X_END (X_START + MAP_WIDTH)
#define Y_END (Y_START + MAP_HEIGHT)

#define MAX_RAY_DISTANCE 300
#define DISTANCE_PER_TURN 1 * CONST

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player 
{
    double			x;
    double			y;
    double		angle;  // in radians
	
	mlx_image_t	*player_img;
} t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	mlx_image_t *rays;
	mlx_image_t *stats;
	t_player	player;

}	t_game;

void	bresenham_line(t_game *game, int start[2], int end[2]);
void	draw_grid(t_game *game, int rows, int cols);
void	draw_player(t_game *game);
void	cast_rays(t_game *game);
void	key_hook(mlx_key_data_t keydata, void *param);
void	print_stats(t_game *game);
void	clean_nicely(t_game *game);

// LIBFT
char	*ft_itoa(int n);
char	*ft_ftoa(float n, int precision);
char	*ft_strjoin(char const *s1, char const *s2);
float	limit_decimal_places(float number, int decimal_places);

#endif