#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

//mini map
#define EMPTY 0
#define WALL 1
#define X_START 50
#define Y_START 50

#define CONST 6
#define ROWS 8
#define COLS 10
#define PIXELS_PER_BLOCK 8
#define PLAYER_SIZE 1
#define PLAYER_DIRECTION_SIZE 50

#define FOV 60.0 // Field of View in degrees
#define RAY_NUMBER 360
#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)

#define MAX_RAY_LENGTH 400
#define MAP_WIDTH COLS * PIXELS_PER_BLOCK * CONST
#define MAP_HEIGHT ROWS * PIXELS_PER_BLOCK * CONST
#define X_END (X_START + MAP_WIDTH)
#define Y_END (Y_START + MAP_HEIGHT)

#define MAX_RAY_DISTANCE 300
#define DISTANCE_PER_TURN 1 * CONST

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 850

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player 
{
    double			x;
    double			y;
    double		angle;  // in radians
	
	mlx_image_t	*player_img;
} t_player;

typedef struct s_ray
{
	int			ray_n;
	float		unit_angle;
	float		current_angle;
	bool		wall_met;
	int			found_vertical_first;
	float		distance;
	t_pos		end;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*map;
	char        	*mapdata;
	mlx_image_t 	*fill;
	mlx_image_t 	*rays;
	t_ray			*ray;
	mlx_image_t 	*stats;
	mlx_image_t 	*player_dir;
	t_player		player;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;

}	t_game;


void	draw_grid(t_game *game, int rows, int cols);
void	draw_player(t_game *game);
void	cast_rays(t_game *game);
void	key_hook(mlx_key_data_t keydata, void *param);
void	print_stats(t_game *game);
void	clean_nicely(t_game *game);
int		distance_to_color(int distance);
void	DDA_ray(t_game *game, t_pos start, t_pos end);
void 	bresenham_ray(t_game *game, t_pos start, t_pos end);
double	get_distance(t_pos start, t_pos end);
int		get_block_index(t_pos *grid_pos);
void 	init_map(t_game *game);

// LIBFT
char	*ft_itoa(int n);
char	*ft_ftoa(float n, int precision);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);


#endif