/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtv1.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:37:09 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/05/29 20:04:14 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RTV1_H
# define FT_RTV1_H
# define WINDOW_X 1300
# define WINDOW_Y 1000
# define IMG_WIDTH 1000
# define IMG_HEIGHT 1000
# define FOV 60
# define ASPECT_RATIO 1
# define THREADS 128
# define RAY_T_MIN 0.00001
# define RAY_T_MAX 1.0e30
# define GAMMA 2.2
# define DISTANCE 5.0
# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

typedef struct		s_vector
{
	double		x;
	double		y;
	double		z;
}					t_vector;

typedef t_vector	t_point;

typedef struct		s_ray
{
	t_point			start;
	t_vector		direction;
	double			t_max;
}					t_ray;

typedef struct		s_plane
{
	t_point			p;
	t_vector		normal;
	int				color;
	double			t1;
	t_vector		rot;
	int				i;
}					t_plane;

typedef struct		s_sphere
{
	t_point			p;
	double			radius;
	int				color;
	double			t1;
	double			t2;
	t_vector		rot;
	int				i;
}					t_sphere;

typedef struct		s_cylinder
{
	t_point			p1;
	t_point			p2;
	double			radius;
	int				color;
	double			t1;
	double			t2;
	t_vector		axis;
	t_vector		rot;
	int				i;
}					t_cylinder;

typedef struct		s_cone
{
	t_point			p1;
	t_point			p2;
	double			angle;
	double			angle_sqr;
	int				color;
	double			t1;
	double			t2;
	t_vector		axis;
	t_vector		rot;
	int				i;
}					t_cone;

typedef struct		s_spot
{
	t_point			p;
	double			intensity;
	int				type;
	int				color;
	int				i;
}					t_spot;

typedef struct		s_intersection
{
	t_ray			ray;
	double			d;
	int				shape;
	double			closest;
	int				hit_index;
	t_vector		hitpoint;
	t_vector		hitnormal;
	double			t1;
	double			t2;
	int				color;
}					t_intersection;

typedef struct		s_camera
{
	t_point			origin;
	t_vector		target;
	t_vector		rot;
	t_vector		forward;
	t_vector		up;
	t_vector		right;
	double			height;
	double			width;
}					t_camera;

typedef struct		s_scene
{
	int				ambient;
	int				ambient_r;
	int				ambient_g;
	int				ambient_b;
	int				speculars;
	int				shadows;
	int				shading;
	char			*name;
}					t_scene;

typedef struct		s_mlx
{
	int			cur_x;
	int			cur_y;
	int			img_width;
	int			img_height;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			thread;
	t_camera	*camera;
	t_scene		*scene;
	t_sphere	spheres[10];
	int			sphere_i;
	t_plane		planes[10];
	int			plane_i;
	t_cylinder	cylinders[10];
	int			cylinder_i;
	t_cone		cones[10];
	int			cone_i;
	t_spot		spots[10];
	int			spot_i;
	int			mousemove;
	int			mouse_1;
	int			mouse_2;
	int			mouse_3;
	int			mouse_x;
	int			mouse_y;
}					t_mlx;

/*
** Vector calculations
*/

t_vector			copy_vector(t_vector v);
t_vector			negative_vector(t_vector v);
t_vector			set_vector(double x, double y, double z);
t_vector			set_single_vector(double d);

t_vector			vector_x(void);
t_vector			vector_y(void);
t_vector			vector_z(void);
t_vector			vector_0(void);

double				dot_vector(t_vector v1, t_vector v2);
t_vector			cross_vector(t_vector v1, t_vector v2);

double				double_sqr(double n);

t_vector			vector_multiply_nb(t_vector v1, double nb);
t_vector			vector_divide_nb(t_vector v1, double nb);

t_vector			normalized_vector(t_vector v);

t_vector			vector_plus(t_vector v1, t_vector v2);
t_vector			vector_minus(t_vector v1, t_vector v2);
t_vector			vector_multiply(t_vector v1, t_vector v2);
t_vector			vector_divide(t_vector v1, t_vector v2);

double				vector_length_pwr2(t_vector v);
double				vector_length(t_vector v);

void				vector_sqr(t_vector *v);
t_vector			vector_sqrd(t_vector v);

void				vector_sqrt(t_vector *v);
t_vector			vector_sqrtd(t_vector v);

/*
** Ray calculations
*/

t_ray				set_ray(t_point start, t_vector direction);
t_ray				copy_ray(t_ray ray1);
t_point				ray_point(t_ray ray, double d);

/*
** Shape calculations
*/

int					plane_intersection(t_plane plane, t_intersection *x, int i);
int					read_plane(t_mlx *mlx, char *line);
int					sphere_intersection(t_sphere sphere,
						t_intersection *x, int i);
int					read_sphere(t_mlx *mlx, char *line);
void				set_cylinder_normal(t_mlx *mlx, t_intersection *x);
int					cylinder_intersection(t_cylinder cone,
						t_intersection *x, int i);
int					read_cyli(t_mlx *mlx, char *line);
void				set_cone_normal(t_mlx *mlx, t_intersection *x);
int					cone_intersection(t_cone cone, t_intersection *x, int i);
int					read_cone(t_mlx *mlx, char *line);

/*
** Intersections
*/

t_intersection		copy_intersection(t_intersection x1);
t_intersection		get_intersection(t_ray ray, t_mlx *mlx);
int					intersected(t_intersection x);
t_point				intersect_pos(t_intersection x, t_ray ray, double d);

/*
** Draw view
*/

void				set_hit_normal(t_mlx *mlx, t_intersection *x);
int					get_color(int x, int y, t_mlx *mlx);
void				*draw_view(void *mlx);

/*
** Camera
*/

void				set_camera(t_mlx *mlx);
void				perspective_cam(t_point origin, t_vector target,
						t_mlx *mlx);
void				read_camera(t_mlx *mlx, char *line);
t_ray				camera_ray(t_camera *camera, t_point point);

/*
** Colors
*/

void				ray_color(t_mlx *mlx, t_intersection *x);

/*
** Read scene
*/

void				int_array_set(int *arr, int n, int nb);
void				int_array_read(int *arr, int n, char *line);
void				read_scene(t_mlx *mlx);

/*
** Utility functions
*/

void				exit_message(char *str);
void				refresh(t_mlx *mlx);
int					exit_free(t_mlx *mlx);
void				add_texts(t_mlx *mlx);
void				add_texts_2(t_mlx *mlx);
void				multi_thread(t_mlx *mlx);
t_vector			rotate_vector(t_vector origin, t_vector target,
						t_vector rot);

/*
** Controls
*/

int					deal_key(int key, t_mlx *mlx);
int					mouse_move(int x, int y, t_mlx *mlx);
int					mouse_release(int button, int x, int y, t_mlx *mlx);
int					mouse_press(int button, int x, int y, t_mlx *mlx);

#endif
