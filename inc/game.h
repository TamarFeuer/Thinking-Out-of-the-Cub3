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
#define PLAYER_SIZE 8
#define PLAYER_DIRECTION_SIZE 50
#define CAMERA_OFFSET_X PLAYER_SIZE / 2 - 1
#define CAMERA_OFFSET_Y PLAYER_SIZE / 2 - 1

//rays
#define MAX_RAY_DISTANCE 400
#define DISTANCE_PER_TURN 0.4 * CONST
#define OUT_OF_BOUNDS INT_MAX

//error logs
#define LOG 80

//map
#define EMPTY '0'
#define WALL '1'
#define SPACE ' '

typedef enum e_intersect_type
{
	INTERSECT_W_HORIZONTAL,
	INTERSECT_W_VERTICAL,
	INTERSECT_NONE
}   t_intersect_type;

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

typedef enum e_ray_sort
{
	PLAYER_DIRECTION,
	CASTED_RAYS,
}	t_ray_sort;

typedef struct s_block_index 
{
	int index;
	int x;
	int y;
} t_block_index;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	t_vec2		pos;
	double		angle;
	int			angle_quad;
}	t_player;

/**
 * @brief Holds all data pertinent to a single ray during the raycasting process.
 * @details This structure encapsulates the geometric properties of a ray,
 *          its state during grid traversal calculations, the results of
 *          potential vertical and horizontal wall hits, and the final
 *          determined hit point and distance for that specific ray cast.
 *
 * Members:
 * @param ray_num Identifier for this specific ray (e.g., column index 0 to SCREEN_WIDTH-1).
 * @param current_angle Absolute angle of the ray in world space (typically radians).
 * @param relative_angle Angle relative to the player's center view direction (used for fish-eye correction).
 * @param tan_current Pre-calculated tangent of current_angle for computational efficiency.
 * @param angle_quad Quadrant (1-4) the current_angle falls into (optimizes stepping direction).
 * @param intersect Current coordinate point being checked during grid traversal calculation.
 * @param ray_step The (dx, dy) step increments used to move between grid intersections.
 * @param v_hit Coordinates of the intersection point if the ray potentially hits a vertical grid line/wall.
 * @param h_hit Coordinates of the intersection point if the ray potentially hits a horizontal grid line/wall.
 * @param distance Calculated final distance to the closest wall hit (potentially corrected for fish-eye).
 * @param is_vertical_first Flag indicating if the vertical hit was closer than the horizontal hit (1=true, 0=false). Consider using bool for clarity.
 * @param end The final world coordinate of the closest wall hit point (selected from v_hit/h_hit).
 * @param wall_met Status flag: true if the ray successfully hit a wall within map bounds, false otherwise.
 */
typedef struct s_ray
{
	int			ray_num;
	double		current_angle;
	double		relative_angle;
	double		tan_current;
	int			angle_quad;
	t_vec2		intersect;
	t_vec2		ray_step;
	t_vec2		v_hit;
	t_vec2		h_hit;
	double		distance;
	bool		is_vertical_first;
	t_vec2		end;
	bool		wall_met;
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
	t_vec2			camera_pos;
	double			pplane;
	mlx_image_t 	*scene;
	mlx_image_t		*mini;
	mlx_image_t 	*stats;
	mlx_texture_t	*textures[4];
	int				number_of_rays;
	t_vec2			ray_end[SCREEN_WIDTH];
}	t_game;

void		draw_grid(t_game *game, int rows, int cols);
void		draw_player(t_game *game);
void		cast_rays(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		print_stats(t_game *game);
void		clean_nicely(t_game *game, char *error_message);
int			distance_to_color(int distance, t_ray_sort ray_sort);
void		draw_bresenham_ray(t_game *game, t_vec2 start, t_vec2 end);
double		get_distance(t_vec2 start, t_vec2 end);
int		 	get_block_index(t_game *game, t_vec2 *grid_pos, t_intersect_type intersect_type);
void 		reach_nearest_wall_by_intersections(t_game *game);
void 		draw_player_direction(t_game *game, t_vec2 start, double angle);
void		normalize_angle_to_2pi(double *angle);
void 		determine_quad(double angle, int *quad);
void		init_game_struct(t_game *game);
void		draw_mmap(void *param);
double		horiz_intersect(t_game *game);
double		vertical_intersect(t_game *game);
bool		is_out_of_bounds(t_game *game, t_vec2 position);
int			is_wall_hit(t_game *game, t_vec2 intersect, t_intersect_type intersect_type);
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

bool		should_continue_stepping(t_game *game, t_vec2 intersect, t_intersect_type intersect_type);
void		put_pixel_scene(t_game *game, int x, int y, u_int32_t color);
void		put_pixel_mmap(t_game *game, int x, int y, u_int32_t color);

#endif
