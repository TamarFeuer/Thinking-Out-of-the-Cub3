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
#include "errors.h"
#include "gnl.h"


#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//map
#define ROWS 6 //8
#define COLS 15 //10
#define EMPTY 0
#define WALL 1

//mini map
#define CONST 4
#define PIXELS_PER_BLOCK 8

#define MMAP_WIDTH COLS * PIXELS_PER_BLOCK * CONST //10*8*6= 480
#define MMAP_HEIGHT ROWS * PIXELS_PER_BLOCK * CONST //8*8*6 = 384
#define X_START 0 // untill 1920 - 860 = 1440??
#define Y_START 0 // ?
#define X_END (X_START + MMAP_WIDTH)
#define Y_END (Y_START + MMAP_HEIGHT)

//player
#define PLAYER_SIZE 1
#define PLAYER_DIRECTION_SIZE 50

//rays
#define FOV 60.0 // Field of View in degrees
#define NUMBER_OF_RAYS 640
#define MAX_RAY_LENGTH 400
#define MAX_RAY_DISTANCE 300
#define DISTANCE_PER_TURN 1 * CONST
#define OUT_OF_BOUNDS 1000000000

//scene
#define SCENE_BLOCK_SIZE 32
#define SCENE_WIDTH  1920
#define SCENE_HEIGHT 1080
#define PROJECTION_DISTANCE 1108
#define FLOOR_COLOR 0xFF00cc40

typedef enum e_direction 
{
	EAST,
	NORTH,
	WEST,
	SOUTH,
} t_direction;

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

// typedef struct s_wall_slice
// {
// 	t_point		point;
// 	float		distance;
// 	double		angle;
// 	float		height;
// 	int			axis;
// 	enum e_side	wall_face;
// }	t_wall_slice;

typedef struct s_bersenham
{
	t_pos		start[SCREEN_WIDTH];
	t_pos		end[SCREEN_WIDTH];
}	t_bresenham;

typedef struct s_player
{
	t_pos		p_pos;
	double		angle;  // in radians
	int			angle_quad;
	mlx_image_t	*player_img;
}	t_player;

typedef struct s_camera
{
	// int		x;
	// int		y;
	t_pos		pos;
	float		pdx;
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
	t_pos		inter;
	int			number_of_rays;
	int			ray_num;
	//float		unit_angle;
	float		current_angle;
	int			angle_quad;
	bool		wall_met;
	int			found_vertical_first;
	float		distance;
	float		corrected_distance;
	t_pos		end_vert;
	t_pos		end_horiz;
	t_pos		v_hit;
	t_pos		h_hit;
	t_pos		ray_start[NUMBER_OF_RAYS];
	t_pos		ray_end[NUMBER_OF_RAYS];
}	t_ray;

typedef struct s_game
{
	bool			is_debug;
	bool			is_mmap;
	mlx_t			*mlx;
	char			*mapdata;
	mlx_image_t 	*fill;
	mlx_image_t 	*scene; //including player
	t_ray			*ray;
	mlx_image_t 	*grid;
	mlx_image_t 	*stats;
	t_player		player;
	t_camera		camera;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;

	char		**map;

}	t_game;


typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
}	t_textures;

typedef struct s_mapdata
{
	char	*path;
	int		total_lines;
	char	**file_data;
	char	**map;
	int		map_rows;
	int		height;
	int		width;
}	t_mapdata;

typedef struct s_data
{
	t_mapdata	map_data;
	t_textures	textures;
}	t_data;


void	bresenham_line(t_game *game, int start[2], int end[2]);
void	draw_grid(t_game *game, int rows, int cols);
void	draw_player(t_game *game);
void	cast_rays(t_game *game);
void	key_hook(mlx_key_data_t keydata, void *param);
void	print_stats(t_game *game);
void	clean_nicely(t_game *game);
int		distance_to_color(int distance);
// void	DDA_ray(t_game *game, t_pos start, t_pos end);
void	DDA_ray(t_game *game, t_pos start, t_pos end, int color);
const char *get_direction(t_game *game);
void	bresenham_ray(t_game *game, t_pos start, t_pos end);
double	get_distance(t_pos start, t_pos end);
int 	get_block_index(t_pos *grid_pos);
int 	get_block_index2(t_game *game, t_pos *grid_pos, int flag);
void	init_map(t_game *game);
void	reach_nearest_wall_by_plotting(t_game *game, float angle);
void 	reach_nearest_wall_by_intersections(t_game *game, float angle);
void 	draw_player_direction(t_game *game, t_pos start, double angle);
void 	draw_the_thing(t_game *game);
void	normalize_angle_to_2pi(float *angle);
void	safe_put_pixel(t_game *game, int x, int y, int color);
int		convert_to_mlx42_endian(int c);
void 	determine_quad(double angle, int *quad);
void	absolute(int *d, int *i);
void	init_game_struct(t_game *game);
void	draw_all(void *param);
float	horiz_intersect(t_game *game, float angle);
float	vertical_intersect(t_game *game, float angle);
bool	is_out_of_bounds(t_pos position);
int		is_wall_hit(t_game *game, t_pos inter, int flag);
int		draw_static_components(t_game *game);


// LIBFT
bool	ft_is_pos_identifier(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char const *str);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
char	*ft_ftoa(float n, int precision);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

float	limit_decimal_places(float number, int decimal_places);
int		ft_isdigit(char c);

// PARSING
char	*get_next_line(int fd);
void	init_data_struct(t_data **data);
void	parse_file(t_data *data, char *file_path);
int		count_lines(char *file_path);
void	copy_line_by_line(t_mapdata *mapinfo, char *file_path);
void 	parse_identifiers(t_data *data, int *i, int *j);
bool	check_file_format(char *file_path);
void 	parse_map(t_data *data, int *i, int *j);
bool	check_map_validity(t_data *data);
bool	is_surrounded_by_walls(t_data *data, char **map);

//PARSING UTILS
void	skip_whitespaces(char **arr, int i, int *j);
void	skip_nl_and_whitespaces(char **arr, int *i, int *j);
void	ft_print_arr(char **arr);

#endif