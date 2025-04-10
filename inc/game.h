#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"


#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)
#define MOUSE_SENSITIVITY 0.1f

//screen
#define SCREEN_WIDTH 1920 // 950
#define SCREEN_HEIGHT 1080 // 500
#define FOV 60.0

//map
#define EMPTY '0'
#define WALL '1'
#define SPACE ' '

//scene
#define SCENE_BLOCK_SIZE 64

//mini map
#define CONST 4
#define MMAP_MAX_HEIGHT SCREEN_HEIGHT/4
#define MMAP_MAX_WIDTH SCREEN_WIDTH/4

//player
#define PLAYER_SIZE 2
#define PLAYER_DIRECTION_SIZE 50
#define FORWARD 1
#define BACKWARD -1

//rays
#define MAX_RAY_DISTANCE 400
#define DISTANCE_PER_TURN 0.4 * CONST
#define OUT_OF_BOUNDS INT_MAX

//error logs
#define LOG 80

typedef enum e_intersection_flag
{
	INTERSECT_W_HORIZONTAL,
	INTERSECT_W_VERTICAL,
	INTERSECT_NONE
}   t_intersection_flag;

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

typedef struct s_block_index 
{
	int index;
	int x;
	int y;
} t_block_index;

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
	t_pos		pos;
	double		angle;
	int			angle_quad;
}	t_player;

typedef struct s_ray
{
	t_pos		end;
	t_pos		intersect;
	int			number_of_rays;
	int			ray_num;
	double		relative_angle;
	double		current_angle;
	double		tan_current;
	int			angle_quad;
	bool		wall_met;
	int			is_vertical_first;
	double		distance;
	t_pos		v_hit;
	t_pos		h_hit;
	t_pos		ray_end[SCREEN_WIDTH];
	int			direction;
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
		uint32_t	rgba[2];
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
	mlx_t			*mlx;
	int				cell_size;
	t_data			*data;
	t_ray			*ray;
	t_player		player;
	t_pos			camera_pos;
	double			pplane;
	mlx_image_t 	*scene;
	mlx_image_t		*mini;
	mlx_image_t 	*stats;
	mlx_texture_t	*textures[4];
}	t_game;

void		draw_grid(t_game *game, int rows, int cols);
void		draw_player(t_game *game);
void		cast_rays(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		print_stats(t_game *game);
void		clean_nicely(t_game *game, char *error_message);
int			distance_to_color(int distance, int flag);
// void	DDA_ray(t_game *game, t_pos start, t_pos end);
void		DDA_ray(t_game *game, t_pos start, t_pos end, int color);
void		draw_bresenham_ray(t_game *game, t_pos start, t_pos end);
double		get_distance(t_pos start, t_pos end);
int		 	get_block_index(t_game *game, t_pos *grid_pos, t_intersection_flag flag);
void 		reach_nearest_wall_by_intersections(t_game *game);
void 		draw_player_direction(t_game *game, t_pos start, double angle);
void		normalize_angle_to_2pi(double *angle);
void		safe_put_pixel(t_game *game, int x, int y, u_int32_t color);
void 		determine_quad(double angle, int *quad);
void		init_game_struct(t_game *game);
void		draw_mmap(void *param);
double		horiz_intersect(t_game *game);
double		vertical_intersect(t_game *game);
bool		is_out_of_bounds(t_game *game, t_pos position);
int			is_wall_hit(t_game *game, t_pos intersect, t_intersection_flag flag);
void		cursor_hook(double xpos, double ypos, void* param);
void		mouse_action (mouse_key_t button, action_t action, modifier_key_t mods, void* param);
int			atoi_limit_255(int *dst, char *str);
void		build_map(char *log, t_game *game);
uint32_t	color_abgr_to_rgba(uint32_t c);
void		del_token(void *token);
void 		draw_scene(t_game *game, t_ray *ray);
void		flood_fill_map(t_game *game, char *dup_map);
void		lexer(t_game *game);
int			min(int a, int b);
int			max(int a, int b);
void		parser(t_game *game);

#endif
