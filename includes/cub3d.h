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

// Errors globals
# define ERR_MLC "Error: Malloc Failed\n"

// Errors fills
# define ERR_FILL_COLORS "Error\n Error fill colors\n"
# define ERR_FILL_MAP "Error\nMap fill error\n"
# define ERR_OPEN_TEXTURES "Error\nCannot open textures\n"
# define ERR_TEXTURES "Error\nTextures values error\n"
# define ERR_FLOOR_CEILING "Error\nFloor and ceiling error\n"

// Sides Error
# define ERR_NO "Error\nError North\n"
# define ERR_SO "Error\nError South\n"
# define ERR_EA "Error\nError East\n"
# define ERR_WE "Error\nError West\n"

// Minimap Colors
# define WALL_COL 0xFFFFFFFF
# define FLOOR_COL 0x000000FF
# define PLAYER_COL 0x00FF00FF

// Screen stuff
# define WIDTH 1024
# define HEIGHT 1024
# define TILE_SIZE 16

# define WALKSPEED .25
# define TURNSPEED .025

# define PI 3.1415926535f
# define HALF_PI PI / 2
# define TWO_PI PI * 2
# define THIRD_PI 3 * PI / 2
# define ONE_DEGREE 0.0174532925f
# define FOV 66

// v2_operations.c
t_vec2		v2_new(double x, double y);
t_vec2		v2_mult(t_vec2 v2, double multiplier);
t_vec2		v2_add(t_vec2 v2, t_vec2 add);
t_vec2		v2_sub(t_vec2 v2, t_vec2 sub);

// for drawing the minimap
void		draw_minimap(t_player player, t_map map);
int			get_char_start(t_map map, int *y, int *x);
void		draw_line(mlx_image_t *img, t_vec2 p1, t_vec2 p2, uint32_t color);

// DDA.c
void		DDA(t_player player, t_map map);

// check_map
int			check_map(t_param *param);

// check_line.c
int			get_str_without_nl(char *line, char **sub);

// parsing.c
int			fill_datas(char *arg, t_param *param);

//! MLX
void		my_hook(void *param);

//! START
int			start(t_param *param, t_window w);

t_shapes	*create_shape_node(void);
t_shapes	*insert_shape_start(t_shapes *head, t_shapes *new_light);
t_shapes	*insert_shape_end(t_shapes *head, t_shapes *new_light);
void		free_shapes_list(t_shapes *head);
void		print_shapes(t_shapes *head);
void		print_flood(t_map map);

//! UTILS
// clean.c
void		clean_everything(t_param *param);

// ft_atof.c
double		ft_atof(char *nptr);

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
