#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//map
#define ROWS 8
#define COLS 10
#define EMPTY 0
#define WALL 1

//mini map
#define CONST 6
#define PIXELS_PER_BLOCK 8

#define MMAP_WIDTH COLS * PIXELS_PER_BLOCK * CONST //10*8*6= 480
#define MMAP_HEIGHT ROWS * PIXELS_PER_BLOCK * CONST //8*8*6 = 384
#define X_START 50 // untill 1920 - 860 = 1440??
#define Y_START 50 // ?


#define X_END (X_START + MMAP_WIDTH)
#define Y_END (Y_START + MMAP_HEIGHT)

//player
#define PLAYER_SIZE 1
#define PLAYER_DIRECTION_SIZE 50

//Rays
#define FOV 60.0 // Field of View in degrees
#define RAY_NUMBER 360
#define MAX_RAY_LENGTH 400
#define MAX_RAY_DISTANCE 300
#define DISTANCE_PER_TURN 1 * CONST

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player 
{
    t_pos		p_pos;
    double		angle;  // in radians
	int			angle_quad;
	mlx_image_t	*player_img;
} t_player;

typedef struct s_camera
{
	int			x;
	float		float_x;
	float		pdx;
	int			y;
	float		float_y;
	float		pdy;
	float		angle;
	float		fov_radi;
	float		plane_distance;
	char		cardinal_point;
	int			direction_flags;
}	t_camera;

typedef struct s_ray
{
	t_pos		end;
	int			ray_n;
	float		unit_angle;
	float		current_angle;
	bool		wall_met;
	int			found_vertical_first;
	float		distance;
	t_pos		end_vert;
	t_pos		end_horiz;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*screen;  //including minimap grid
	char        	*mapdata;
	mlx_image_t 	*fill;
	mlx_image_t 	*rays; //including player
	t_ray			*ray;
	mlx_image_t 	*stats;
	mlx_image_t 	*scene;
	t_player		player;
	t_camera		camera;
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
void	bresenham_ray(t_game *game, t_pos start, t_pos end);
double	get_distance(t_pos start, t_pos end);
int		get_block_index(t_pos *grid_pos);
void	init_map(t_game *game);
void	reach_nearest_wall_block(t_game *game, t_pos start, double angle);
void 	reach_nearest_wall_block2(t_game *game, double angle);
void 	draw_player_direction(t_game *game, t_pos start, double angle);

// LIBFT
char	*ft_itoa(int n);
char	*ft_ftoa(float n, int precision);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);


#endif