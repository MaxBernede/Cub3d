#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "struct.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define OK 0
# define ERROR 1

// Run errors
# define ERR_START_POS "Position not found\n"
# define ERR_CHARACTER "Character not found or more than 1 time in the file\n"
# define ERR_ARG "Error: Not enough arguments\nShould be ./cub3d 'file.cub'\n"
# define ERR_FILE "Error: File given doesn't exist or no rights to access it\n"
# define ERR_NOCUB "Error: File doesn't end with .cub, cannot be accepted\n"
# define ERR_FILE_DATA "Error: File datas are not correct, exit\n"
# define ERR_EMPTY_MAP "Error\nMap is empty\n"
# define ERR_NO_MAP "Error\nNo map in\n"

// Errors globals
# define ERR_MLC "Error: Malloc Failed\n"

// Errors fills
# define ERR_FILL_COLORS "Error\n Error fill colors\n"
# define ERR_FILL_MAP "Error\nMap fill error\n"
# define ERR_OPEN_TEXTURES "Error\nCannot open textures\n"
# define ERR_TEXTURES "Error\nTextures values error\n"
# define ERR_FLOOR_CEILING "Error\nFloor and ceiling error\n"
# define ERR_TYPE "Error\nParsing type data incorrect\n"

// Sides Error
# define ERR_NO "Error\nError North\n"
# define ERR_SO "Error\nError South\n"
# define ERR_EA "Error\nError East\n"
# define ERR_WE "Error\nError West\n"

// Minimap Colors
# define WALL_COL 0xFFFFFF5A
# define NO_FLOOR_COL 0x808080FF
# define PLAYER_COL 0x00FF00FF

//Wall color test
# define SILVER 0xC0C0C0FF
# define BLUE 0x00FFFFFF
# define GREEN 0x008000FF
# define PURPLE 0x800080FF

// Screen dimentions
# define WIDTH 1024
# define HEIGHT 512

// map/world tile size
# define TILE_SIZE 8

// Player variables
# define WALKSPEED 15
# define TURNSPEED 1.5
# define FOV 64

// Rendering Variables
# define HALF_HEIGHT HEIGHT / 2
# define SHARPNESS 8
# define RAY_AMOUNT FOV * SHARPNESS

// Math for raycasting & rendering
# define PI 3.1415926535f
# define HALF_PI PI / 2
# define TWO_PI PI * 2
# define THIRD_PI 3 * PI / 2
# define ONE_DEGREE 0.0174532925f
# define DEGREE_STEP ONE_DEGREE / SHARPNESS

//Type of datas
# define FLOOR 2
# define CEILING 3
# define NORTH 4
# define SOUTH 5
# define EAST 6
# define WEST 7

//fill_datas.c
int			fill_texture(mlx_texture_t **texture, char *s);
int			floor_ceiling(int type, char *arg, t_param *p);

//parsing.c
int			parse_file(char *arg, t_param *p);

//gets.c
char		**get_map(t_param *p);
int			get_type(char *line);
int			get_type_no_space(char *line);
int			get_char_start(t_map map, int *y, int *x);

//flood_fill.c
int			flood_fill(t_map map, int x, int y);

// v2_operations.c
t_vec2		v2_new(double x, double y);
t_vec2		v2_mult(t_vec2 v2, double multiplier);
t_vec2		v2_add(t_vec2 v2, t_vec2 add);
t_vec2		v2_sub(t_vec2 v2, t_vec2 sub);

// for drawing the minimap
int			get_char_start(t_map map, int *y, int *x);
void		draw_line(mlx_image_t *img, t_vec2 p1, t_vec2 p2, uint32_t color);

// DDA.c
void		init_dda(t_dda *data, float player_angle);
void		dda(t_dda *data, t_vec2 player_pos, t_map map);

// renderer.c
void		renderer(t_param *param ,t_player player, t_map map, mlx_image_t *reality);

// check_map
int			check_map(t_param *param);

// check_line.c
int			get_str_without_nl(char *line, char **sub);
char 		*get_str_no_space(char *line);

//! MLX
void		my_hook(void *param);

//! START
int			start(t_param *param, t_window w);

char*		concatenateStrings(char** strings, int numStrings);

void		print_flood(t_map map);

//!Color_wall
uint32_t get_color_wall(mlx_texture_t* texture, float percentageX, float percentageY);

//! UTILS
// clean.c
void		clean_everything(t_param *param);

float pourcentage_of(float coordinate);

// ft_atof.c
double		ft_atof(char *nptr);

//normalize.c
void		normalize_map(t_param *p);

// to.c
int			to_decimal(char *s, double *f);

int			is_scale(char *s, double *f);
int			is_colors(char *s, int *r, int *g, int *b);

void		ft_2d_print(char **str);
int			cmp(char *s1, char *s2);
int			nb_or_comma(char *s);

// valid_input.c
bool		check_file(char *arg);
int			open_file(char *arg);

// map_parse
char		**get_map(t_param *p);
int			parse_map(char *line, t_param *param);

// nodes
void		print_list(t_node *head);
void		ft_free_lst(t_node *head);
void		ft_free_node(t_node *node);
int			insert_node(t_node **head, char *line);
int			ft_our_lst_size(t_node *lst);

#endif
