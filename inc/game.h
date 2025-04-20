/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:20:08 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 19:31:48 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libs/libft/libft.h"
# include "MLX42.h"

# define PI 3.141592653
# define DEG_TO_RAD 0.017453293
# define MOUSE_SENSITIVITY 0.006283185

//screen
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define FOV 60.0

//map
# define EMPTY '0'
# define WALL '1'
# define SPACE ' '

//scene
# define SCENE_BLOCK_SIZE 64

//mini map
# define CONST 4
# define COLOR_MMAP_GRID 0x777777FF

//player
# define PLAYER_SIZE 8
# define PLAYER_DIRECTION_SIZE 50

//rays
# define MAX_RAY_DISTANCE 400
# define OUT_OF_BOUNDS INT_MAX

//error logs
# define LOG 80

typedef enum e_intersect_type
{
	INTERSECT_W_HORIZONTAL,
	INTERSECT_W_VERTICAL,
	INTERSECT_NONE
}	t_intersect_type;

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
	int	index;
	int	x;
	int	y;
}	t_block_index;

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

typedef struct s_bresenham_params
{
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;
	int		abs_dx;
	int		abs_dy;
	int		step_x;
	int		step_y;
	t_vec2	start;
}	t_bresenham_params;

typedef struct s_player
{
	t_vec2		pos;
	double		angle;
	int			angle_quad;
}	t_player;

/**
 * @brief Holds all data pertinent to a single ray during raycasting.
 *
 * @details This structure encapsulates the geometric properties of a ray,
 *          its state during grid traversal, the results of potential wall
 *          hits (vertical/horizontal), and the final hit point and distance.
 *
 * Members:
 * @param ray_num Identifier for this ray.
 * @param current_angle Absolute angle of the ray in world space (radians).
 * @param relative_angle Angle relative to player’s direction (for fish-eye fix).
 * @param tan_current Pre-computed tangent of current_angle for performance.
 * @param angle_quad Quadrant (1-4) current_angle falls into (aids step logic).
 * @param intersect Current coordinate being tested during grid traversal.
 * @param ray_step The (dx, dy) steps to move between grid intersections.
 * @param v_hit Coordinates where ray may hit a vertical wall/grid line.
 * @param h_hit Coordinates where ray may hit a horizontal wall/grid line.
 * @param distance Final distance to closest wall hit.
 * @param is_vertical_first 1 if vertical hit is closer than horizontal (else 0).
 * @param end Final world coordinates of the closest wall hit (from v_hit/h_hit).
 * @param wall_met True if a wall was hit within map bounds, false otherwise.
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
}	t_data;

typedef struct s_game
{
	bool			is_debug;
	bool			is_mmap;
	bool			is_mouse_active;
	mlx_t			*mlx;
	int				cell_size;
	double			step;
	t_data			*data;
	t_ray			*ray;
	t_player		player;
	t_vec2			camera_pos;
	double			pplane;
	mlx_image_t		*scene;
	mlx_image_t		*mini;
	mlx_image_t		*stats;
	mlx_texture_t	*textures[4];
	int				number_of_rays;
	t_vec2			ray_end[SCREEN_WIDTH];
}	t_game;

//PARSING
void		lexer(t_game *game);
void		parser(t_game *game);
void		flood_fill_map(t_game *game, char *dup_map);
int			atoi_limit_255(int *dst, char *str);
void		build_map(char *log, t_game *game);
uint32_t	color_abgr_to_rgba(uint32_t c);
void		del_token(void *token);

//MINIMAP
void		draw_mmap(void *param);
void		draw_grid(t_game *game, int rows, int cols);
void		draw_player(t_game *game);
void		draw_player_direction(t_game *game, t_vec2 start, double angle);
void		draw_bresenham_ray(t_game *game, t_vec2 start, t_vec2 end);
void		print_stats(t_game *game);
void		put_pixel_mmap(t_game *game, int x, int y, u_int32_t color);
void		clear_image(mlx_image_t *image, uint32_t npixels);
int			distance_to_color(int distance, t_ray_sort ray_sort);

//RAY CASTING
void		cast_rays(t_game *game);
void		reach_nearest_wall_by_intersections(t_game *game);
double		horiz_intersect(t_game *game);
double		vertical_intersect(t_game *game);
double		get_distance(t_vec2 start, t_vec2 end);

//SCENE
void		draw_scene(t_game *game, t_ray *ray);
void		put_pixel_scene(t_game *game, int x, int y, u_int32_t color);

//HOOKS
void		key_hook(mlx_key_data_t keydata, void *param);
void		cursor_hook(double xpos, double ypos, void *param);
void		mouse_action(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param);

//WALL HITS AND COLLISION
void		check_collision(t_game *game, t_vec2 old_pos, t_vec2 new_pos);
int			get_block_index(t_game *game, t_vec2 *grid_pos, \
	t_intersect_type intersect_type);
bool		is_out_of_bounds(t_game *game, t_vec2 position);
int			is_wall_hit(t_game *game, t_vec2 intersect, \
	t_intersect_type intersect_type);

//UTILS
int			min(int a, int b);
int			max(int a, int b);
void		plot_adjacent_pixels(t_game *game, t_vec2 center, int color);
void		normalize_angle_to_2pi(double *angle);
void		determine_quad(double angle, int *quad);

//START AND FINISH
void		init_game_struct(t_game *game);
void		clean_nicely(t_game *game, char *error_message);

#endif
