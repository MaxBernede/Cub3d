#ifndef STRUCT_H
# define STRUCT_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_ray_data
{
	t_vec2	hit;
	t_vec2	ray_step;
	t_vec2	origin;
	float	length;
}	t_ray;

typedef struct s_dda_data
{
	t_ray	xray;
	t_ray	yray;
	t_vec2	hit;
	float	angle;
	int		rays;
}			t_dda;

typedef struct s_window
{
	int				width;
	int				height;
}					t_window;

typedef struct s_lkd_list
{
	double			scale;
	t_vec3			p;
	t_color			color;
	struct s_list	*next;
}					t_lkd_list;

typedef struct s_shapes
{
	t_vec3			p;
	t_vec3			vec;
	t_color			color;
	struct s_shapes	*next;
}					t_shapes;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	delta;
	int		fov;
	float	angle;
}			t_player;

typedef struct s_map
{
	char			**flood;
	char			**map;
	int				length;
	int				height;

	mlx_image_t		*minimap;
}					t_map;

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct s_param
{
	t_color			floor;
	t_color			ceiling;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				fd;
	bool			end_map_parse;
	t_node			*tmp_map;
	t_map			map;
	t_player		player;

	mlx_t			*mlx;
	mlx_image_t		*img;
	t_window		window;
	t_shapes		*shapes;
}					t_param;

#endif
