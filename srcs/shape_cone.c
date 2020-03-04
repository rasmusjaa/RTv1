/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/03/04 14:33:48 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
*/

static void	set_cone_hit(t_cone cone, t_intersection *x, double d, int i)
{
	x->closest = d;
	x->color = cone.color;
	x->shape = CONE;
	x->hit_index = i;
}

static int	split_cone(t_cone cone, t_intersection *x, double d)
{
	t_vector	hitpoint;

	hitpoint = ray_point(x->ray, d);
	if (dot_vector(vector_minus(hitpoint, cone.p1), cone.axis) > 0)
		return (1);
	return (0);
}

int			cone_intersection(t_cone cone, t_intersection *x, int i)
{
	t_vector	to_cone;
	t_vector	quad;
	double		d;

	to_cone = vector_minus(x->ray.start, cone.p1);
	quad.x = dot_vector(x->ray.direction, cone.axis);
	quad.x = quad.x * quad.x - cone.angle_sqr;
	quad.y = 2 * (dot_vector(x->ray.direction, cone.axis) *
		dot_vector(to_cone, cone.axis) - dot_vector(x->ray.direction, to_cone) *
		cone.angle_sqr);
	quad.z = dot_vector(to_cone, cone.axis) * dot_vector(to_cone, cone.axis) -
		dot_vector(to_cone, to_cone) * cone.angle_sqr;
	d = double_sqr(quad.y) - 4 * quad.x * quad.z;
	if (d < 0.0)
		return (0);
	x->t1 = (-1 * quad.y - sqrt(d)) / (2 * quad.x);
	x->t2 = (-1 * quad.y + sqrt(d)) / (2 * quad.x);
	if (split_cone(cone, x, x->t2) == 3)
		return (0);
	if (x->t2 > RAY_T_MIN && x->t2 < x->closest)
		set_cone_hit(cone, x, x->t2, i);
	if (x->t1 > RAY_T_MIN && x->t1 < x->closest)
		set_cone_hit(cone, x, x->t1, i);
	return (d == 0) ? (1) : (2);
}

static void	set_cone(t_cone *cone)
{
	if (cone->p1.x == cone->p2.x && cone->p1.y == cone->p2.y &&
		cone->p1.z == cone->p2.z)
		cone->p2.y = cone->p1.y + 1;
	cone->p2 = rotate_vector(cone->p1, cone->p2, cone->rot);
	cone->axis = vector_minus(cone->p1, cone->p2);
	cone->axis = normalized_vector(cone->axis);
	cone->angle = cos(cone->angle * M_PI / 180.0);
	cone->angle_sqr = cone->angle * cone->angle;
}

int			read_cone(t_mlx *mlx, char *line)
{
	int		arr[13];

	int_array_set(arr, 13, 0);
	int_array_read(arr, 13, line);
	arr[7] = ft_int_clamp_0(arr[7], 0, 255);
	arr[8] = ft_int_clamp_0(arr[8], 0, 255);
	arr[9] = ft_int_clamp_0(arr[9], 0, 255);
	mlx->cones[mlx->cone_i].p1.x = ft_int_clamp_0(arr[0], -99, 99);
	mlx->cones[mlx->cone_i].p1.y = ft_int_clamp_0(arr[1], -99, 99);
	mlx->cones[mlx->cone_i].p1.z = ft_int_clamp_0(arr[2], -99, 99);
	mlx->cones[mlx->cone_i].p2.x = ft_int_clamp_0(arr[3], -99, 99);
	mlx->cones[mlx->cone_i].p2.y = ft_int_clamp_0(arr[4], -99, 99);
	mlx->cones[mlx->cone_i].p2.z = ft_int_clamp_0(arr[5], -99, 99);
	mlx->cones[mlx->cone_i].angle = ft_int_clamp(arr[6], 1, 45);
	mlx->cones[mlx->cone_i].color = arr[7] << 16 | arr[8] << 8 | arr[9];
	mlx->cones[mlx->cone_i].rot.x = ft_int_clamp_0(arr[10], -180, 180);
	mlx->cones[mlx->cone_i].rot.y = ft_int_clamp_0(arr[11], -180, 180);
	mlx->cones[mlx->cone_i].rot.z = ft_int_clamp_0(arr[12], -180, 180);
	set_cone(&mlx->cones[mlx->cone_i]);
	return (0);
}
