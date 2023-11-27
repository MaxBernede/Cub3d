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
#define ERR_ARG "Error: Not enough arguments to run\nShould be ./cub3d 'file.cub'\n"
#define ERR_FILE "Error: File given doesn't exist or no rights to access it\n"
#define ERR_NORT "Error: File doesn't end with .rt, cannot be accepted\n"
#define ERR_FILE_DATA "Error: File datas are not correct, exit\n"

//Errors globals
#define ERR_MLC "Error: Malloc Failed\n"

//Errors fills
#define ERR_FILL_COLORS "Error\n Error fill colors\n"
#define ERR_FILL_MAP "Error\nMap fill error\n"
#define ERR_OPEN_TEXTURES "Error\nCannot open textures\n"
#define ERR_TEXTURES "Error\nTextures sides error\n"
#define ERR_FLOOR_CEILING "Error\nFloor and ceiling error\n"

//Sides Error
#define ERR_NO "Error\nError North\n"
#define ERR_SO "Error\nError South\n"
#define ERR_EA "Error\nError East\n"
#define ERR_WE "Error\nError West\n"

//check_line.c
int	get_str_without_nl(char *line, char **sub);

//parsing.c
int	fill_datas(char *arg, t_param *param);

//!MLX
void my_hook(void* param);

//!START
int start(t_param *param, t_window w);

t_shapes *create_shape_node();
t_shapes *insert_shape_start(t_shapes *head, t_shapes *new_light);
t_shapes *insert_shape_end(t_shapes *head, t_shapes *new_light);
void free_shapes_list(t_shapes *head);
void print_shapes(t_shapes *head);

//!UTILS
//clean.c
void clean_everything(t_param *param);

//ft_atof.c
double ft_atof(char *nptr);

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