#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "struct.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define OK 0
#define ERROR 1

//Run errors
#define ERR_ARG "Error: Not enough arguments to run\nShould be ./cub3d 'file.rt'\n"
#define ERR_FILE "Error: File given doesn't exist or no rights to access it\n"
#define ERR_NORT "Error: File doesn't end with .rt, cannot be accepted\n"
#define ERR_FILE_DATA "Error: File datas are not correct, exit\n"

//Errors globals
#define ERR_MLC "Error: Malloc Failed\n"

//Errors fills
#define ERR_FILL_MAP "Error\nMap fill error\n"
#define ERR_OPEN_TEXTURES "Error\nCannot open textures\n"
#define ERR_TEXTURES "Error\nTextures sides error\n"
#define ERR_FLOOR_CEILING "Error\nFloor and ceiling error\n"
#define ERR_FILL_SCALE "Error: Error data filling the scale\n"
#define ERR_FILL_COLORS "Error: Error data filling the colors\n"
#define ERR_FILL_POSITION "Error: Error data filling the position\n"
#define ERR_FILL_VECTOR "Error: Error data filling the vector\n"
#define ERR_FILL_RADIUS "Error: Error data filling the radius\n"
#define ERR_FILL_HEIGHT "Error: Error data filling the height\n"
#define ERR_ADD_PARAM "Error: the first character of add param isn't correct\n"
#define ERR_ADD_SHAPE "Error: the type of shape from add shape isn't correct\n"


//Sides Error
#define ERR_NO "Error\nError North\n"
#define ERR_SO "Error\nError South\n"
#define ERR_EA "Error\nError East\n"
#define ERR_WE "Error\nError West\n"

//Shape Error
#define ERR_PL "Error: Shape Plane fill\n"
#define ERR_SQ "Error: Shape Square fill\n"
#define ERR_SP "Error: Shape Sphere fill\n"
#define ERR_TR "Error: Shape Triangle fill\n"
#define ERR_CY "Error: Shape Cylinder fill\n"

#define ERR_CAM "Error: Camera informations incorrect\n"
#define ERR_AMB_LIGHT "Error: Ambiant lights informations incorrect\n"
#define ERR_LIGHT "Error: Lights informations incorrect\n"
#define ERR_WINDOW "Error: Window informations incorrect\n"

//fill_params.c
int add_param(char **split, t_param *param);

//parsing.c
int	fill_datas(char *arg, t_param *param);

//!MLX
void my_hook(void* param);

//!START
int start(t_param *param, t_window w);

//!SHAPES
int add_shape(char **split, t_param *param);

t_shapes *create_shape_node();
t_shapes *insert_shape_start(t_shapes *head, t_shapes *new_light);
t_shapes *insert_shape_end(t_shapes *head, t_shapes *new_light);
void free_shapes_list(t_shapes *head);
void print_shapes(t_shapes *head);

//!UTILS
//prints.c
void print_shape(t_shapes *s);
void print_param(t_param *param);


//clean.c
void clean_everything(t_param *param);

//ft_atof.c
double ft_atof(char *nptr);
//is_camera.c
int is_fov(char *s, int *fov);
int	is_coords(char *s, double *x, double *y, double *z);
int	is_vectors(char *s, double *r, double *g, double *b);
int	fill_double(char *s, double *f);

//is_numbers.c
int is_numbers(char *a, char *b, char *c);
int ft_is_number(char *s);
int is_neg_numbers(char *a, char *b, char *c);
int ft_is_neg_number(char *s);
int is_neg_deci_numbers(char *a, char *b, char *c);
int is_neg_deci_nb(char *s);
int is_doubles(char *a, char *b, char *c);
int ft_is_f(char *s);

//to.c
int	to_decimal(char *s, double *f);

int is_scale(char *s, double *f);
int	is_colors(char *s, int *r, int *g, int *b);

void	ft_2d_print(char **str);
int	cmp(char *s1, char *s2);
int nb_or_comma(char *s);

//valid_input.c
bool	check_file(char *arg);
int		open_file(char *arg);

//map_parse
char	**get_map(t_param *p);
int		parse_map(char *line, t_param *param);

//nodes
void	print_list(t_node *head);
void	ft_free_lst(t_node *head);
void	ft_free_node(t_node *node);
int		insert_node(t_node **head, char *line);
int		ft_our_lst_size(t_node *lst);


#endif