#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"


#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)
#define SCREEN_WIDTH 1920 //950//1920
#define SCREEN_HEIGHT 1080 //500//1080
#define MOUSE_SENSITIVITY 0.1f

//map
#define EMPTY '0'
#define WALL '1'
#define SPACE ' '

//mini map
#define CONST 4
#define PIXELS_PER_BLOCK 8

//#define MMAP_WIDTH COLS * PIXELS_PER_BLOCK * CONST
//#define MMAP_HEIGHT ROWS * PIXELS_PER_BLOCK * CONST
#define X_START 0
#define Y_START 0
#define X_END (X_START + MMAP_WIDTH)
#define Y_END (Y_START + MMAP_HEIGHT)
#define MMAP_MAX_HEIGHT SCREEN_HEIGHT/4
#define MMAP_MAX_WIDTH SCREEN_WIDTH/4

//player
#define PLAYER_SIZE 2
#define PLAYER_DIRECTION_SIZE 50

//rays
#define FOV 60.0 // Field of View in degrees
#define FRUSTUM_PLANE (SCREEN_WIDTH / 2.0 / tan(FOV * DEG_TO_RAD / 2.0))
#define NUMBER_OF_RAYS 640
#define MAX_RAY_LENGTH 400
#define MAX_RAY_DISTANCE 300
#define DISTANCE_PER_TURN 0.5 * CONST
#define OUT_OF_BOUNDS 1000000000

//scene
#define SCENE_BLOCK_SIZE 64
#define SCENE_WIDTH  1920
#define SCENE_HEIGHT 1080
#define BASE_FRUSTUM_DISTANCE 300.0f
#define MIN_RAY_DISTANCE 5.0f
#define FLOOR_COLOR 0xFF8000FF  //---> !

//error logs
#define LOG 80

enum e_dir
{
	E,
	N,
	W,
	S
};

enum e_horizon
{
	FL,
	CE
};

enum e_rgb
{
	RED,
	GREEN,
	BLUE
};

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	t_pos		p_pos;  // ---> !
	double		angle;  // in radians ---> !
	int			angle_quad;
}	t_player;

typedef struct s_camera
{
	t_pos		pos;
	float		angle;
}	t_camera;

typedef struct s_mmap
{
	int block_size;
	int height;
	int width;
} t_mmap;

typedef struct s_ray
{
	t_pos		end;
	t_pos		intersect;
	int			number_of_rays;
	int			ray_num;
	double		current_angle;
	int			angle_quad;
	bool		wall_met;
	int			is_vertical_first;
	float		distance;
	float		corrected_distance;
	t_pos		v_hit;
	t_pos		h_hit;
	t_pos		ray_start[SCREEN_WIDTH];
	t_pos		ray_end[SCREEN_WIDTH];
}	t_ray;

typedef struct s_data
{
	char	*map;
	char	*cub_file;
	t_list	*tokens;
	t_list	*map_tokens;
	int		parsed[2];
	struct s_mapdata
	{
		int			rows;
		int			cols;
		u_int32_t	rgba[2];
		char		*texture_files[4];
	}		map_data;
	struct s_minimap
	{
		int width;
		int	height;
		int	x_start;
		int	x_end;
		int	y_start;
		int	y_end;
		int max_height;
		int	max_width;
	}		minimap_data;
}	t_data;

typedef struct s_game
{
	bool			is_debug;
	bool			is_mmap;
	bool			is_mouse_active;
	int				cell_size;
	t_data			*data;
	t_ray			*ray;
	t_mmap			mmap;
	t_player		player;
	t_camera		camera;
	mlx_t			*mlx;
	mlx_image_t 	*scene;
	mlx_image_t 	*stats;
	mlx_texture_t	*textures[4];
}	t_game;

void	draw_grid(t_game *game, int rows, int cols);
void	draw_player(t_game *game);
void	cast_rays(t_game *game);
void	key_hook(mlx_key_data_t keydata, void *param);
void	print_stats(t_game *game);
void	clean_nicely(t_game *game, char *error_message);
int		distance_to_color(int distance);
// void	DDA_ray(t_game *game, t_pos start, t_pos end);
void	DDA_ray(t_game *game, t_pos start, t_pos end, int color);
const char *get_direction(t_game *game);
void	draw_bresenham_ray(t_game *game, t_pos start, t_pos end);
double	get_distance(t_pos start, t_pos end);
int		get_block_index(t_game *game, t_pos *grid_pos, int flag);
int 	get_block_index2(t_game *game, t_pos *grid_pos, int flag);
void	reach_nearest_wall_by_plotting(t_game *game, float angle);
void 	reach_nearest_wall_by_intersections(t_game *game);
void 	draw_player_direction(t_game *game, t_pos start, double angle);
void 	draw_scene(t_game *game);
void	normalize_angle_to_2pi(double *angle);
void	safe_put_pixel(t_game *game, int x, int y, u_int32_t color);
int		convert_to_mlx42_endian(int c);
void 	determine_quad(double angle, int *quad);
void	absolute(int *d, int *i);
void	init_game_struct(t_game *game);
void	draw_all(void *param);
float	horiz_intersect(t_game *game);
float	vertical_intersect(t_game *game);
bool	is_out_of_bounds(t_game *game, t_pos position);
int		is_wall_hit(t_game *game, t_pos intersect, int flag);
int		draw_static_components(t_game *game);

void 	cursor_hook(double xpos, double ypos, void* param);
void mouse_action (mouse_key_t button, action_t action, modifier_key_t mods, void* param);

int		atoi_limit_255(int *dst, char *str);
void	build_map(char *log, t_game *game);
void	del_token(void *token);
void	flood_fill_map(t_game *game, char *dup_map);
void	lexer(t_game *game);
void	parser(t_game *game);

#endif
