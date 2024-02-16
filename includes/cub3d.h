/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 18:47:10 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/16 18:55:33 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define OK 0
# define ERROR 1

# define ERR_START_POS "Position not found\n"
# define ERR_CHARACTER "Character not found or more than 1 time in the file\n"
# define ERR_ARG "Error: Not enough arguments\nShould be ./cub3d 'file.cub'\n"
# define ERR_FILE "Error: File given doesn't exist or no rights to access it\n"
# define ERR_NOCUB "Error: File doesn't end with .cub, cannot be accepted\n"
# define ERR_FILE_DATA "Error: File datas are not correct, exit\n"
# define ERR_EMPTY_MAP "Error\nMap is empty\n"
# define ERR_NO_MAP "Error\nNo map in\n"
# define ERR_IMG_CREA "Error\nWhile creating MLX images\n"

# define ERR_MLC "Error: Malloc Failed\n"

# define ERR_FILL_COLORS "Error\n Error fill colors\n"
# define ERR_FILL_MAP "Error\nMap fill error\n"
# define ERR_OPEN_TEXTURES "Error\nCannot open textures\n"
# define ERR_TEXTURES "Error\nTextures values error\n"
# define ERR_FLOOR_CEILING "Error\nFloor and ceiling error\n"
# define ERR_TYPE "Error\nParsing type data incorrect\n"
# define ERR_NOTEXT "Error\ndoor or key but no texture\n"

# define ERR_NO "Error\nError North\n"
# define ERR_SO "Error\nError South\n"
# define ERR_EA "Error\nError East\n"
# define ERR_WE "Error\nError West\n"
# define ERR_DOOR "Error\nError Door\n"
# define ERR_KEY "Error\nError Key\n"

# define WALL_COL 0xFFFFFF5A
# define RAY_COL 0xFFFF00FF
# define PLAYER_COL 0x00FF00FF
# define DOOR_COL 0xd1001F5A
# define KEY_COL 0x8B9A465F

# define SILVER 0xC0C0C0FF
# define BLUE 0x00FFFFFF
# define GREEN 0x008000FF
# define PURPLE 0x800080FF

# define WIDTH 1024
# define HEIGHT 512
# define HALF_HEIGHT 256

# define CELL_SIZE 8

# define WALKSPEED 15
# define TURNSPEED 2.5
# define MOUSESPEED .05
# define FOV .8

# define PI 3.14159265359f
# define HALF_PI 1.57079632679f
# define TWO_PI 6.28318530718f
# define THIRD_PI 4.71238898038f
# define ONE_DEGREE 0.0174532925f

# define FLOOR 2
# define CEILING 3
# define NORTH 4
# define SOUTH 5
# define EAST 6
# define WEST 7
# define DOOR 8
# define KEY 9

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "struct.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

//player.c
void		fill_delta(t_player *player, t_vec2 *offset);
void		move_player(t_param *p, bool strafing, int direction, double dt);
void		change_player_angle(t_player *player, double turnspeed, double dt);
void		init_player(t_map map, t_player *player);
void		open_door(t_player *player, t_map *map);

//valid_input.c
bool		endswith(char *str, char *suffix);

//wall.c
void		draw_wall(t_param *param, t_dda data);

//fill_datas.c
int			fill_texture(int t, t_param *p, char *s);
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
void		put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void		draw_line(mlx_image_t *img, t_vec2 p1, t_vec2 p2, uint32_t color);

// DDA.c
void		dda(t_dda *data, t_player *player, t_map map, char *hit_condition);

// renderer.c
void		render(t_param *param);

// check_map
int			check_map(t_param *param);
int			check_full_textures(t_param *p);
int			search_in_map(t_param *p, char *c);

// check_line.c
int			get_str_without_nl(char *line, char **sub);
char		*get_str_no_space(char *line);

//! MLX
void		cursor_hook(double x, double y, void *param);
void		my_hook(void *param);

//! START
int			start(t_param *param);

char		*concatenate_strings(char **strings, int num_string);

void		print_flood(t_map map);

//! UTILS
// clean.c
void		clean_everything(t_param *param);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

float		pourcentage_of(float coordinate);

// fix_angle.c
float		fix_angle(float angle);

// ft_atof.c
double		ft_atof(char *nptr);

//normalize.c
void		normalize_map(t_param *p);

// to.c
int			to_decimal(char *s, double *f);

int			is_colors(char *s, int *r, int *g, int *b);

void		ft_2d_print(char **str);
int			cmp(char *s1, char *s2);
int			nb_or_comma(char *s);

//utils2.c
float		float_modulo(float dividend, float divisor);
float		pourcentage_of(float coordinate);
void		print_all_ray(t_ray *ray);

// valid_input.c
bool		check_file(char *arg);
int			open_file(char *arg);

// map_parse
int			parse_map(char *line, t_param *param);

// nodes
void		print_list(t_node *head);
void		ft_free_lst(t_node *head);
void		ft_free_node(t_node *node);
int			insert_node(t_node **head, char *line);
int			ft_our_lst_size(t_node *lst);
char		*ft_strchr_nolast(const char *s, int c);

#endif
