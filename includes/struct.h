#ifndef STRUCT_H
#define STRUCT_H

#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_vec3
{
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_window
{
	int width;
	int height;
}	t_window;
typedef struct s_lkd_list
{
	double scale;
	t_vec3 p;
	t_color color;
	struct s_list *next;
}	t_lkd_list;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_shapes
{
	t_vec3 p;
	t_vec3 vec;
	t_color color;
	struct s_shapes *next;
}	t_shapes;

typedef struct s_map
{
	char **map;
	int length;
	int height;
}	t_map;

typedef struct s_param
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_window	window;
	t_color		floor;
	t_color		ceiling;
	int			fd_no;
	int			fd_so;
	int			fd_we;
	int			fd_ea;
	t_shapes	*shapes;
}	t_param;


#endif