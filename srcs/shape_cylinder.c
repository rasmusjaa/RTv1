/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 18:14:40 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
*/

static void	set_cylinder_hits(t_cylinder cylinder, t_intersection *x, double d, int i)
{
	x->closest = d;
	x->color = cylinder.color;
	x->shape = CYLINDER;
	x->hit_index = i;
}

int			cylinder_intersection(t_cylinder cylinder, t_intersection *x, int i)
{
	t_vector	to;
	t_vector	to_x;
	t_vector	ray_x;
	t_vector	quad;
	double		t1;
	double		t2;
	double		d;

	to = vector_minus(x->ray.start, cylinder.p1);
	to_x = cross_vector(to, cylinder.axis);
	ray_x = cross_vector(x->ray.direction, cylinder.axis);
	quad.x = dot_vector(ray_x, ray_x);
	quad.y = 2 * dot_vector(ray_x, to_x);
	quad.z = dot_vector(to_x, to_x) - cylinder.radius * cylinder.radius *
		dot_vector(cylinder.axis, cylinder.axis);
	d = double_sqr(quad.y) - 4 * quad.x * quad.z;
	if (d < 0.0)
		return (0);
	t1 = (-1 * quad.y - sqrt(d)) / (2 * quad.x);
	if (t1 > RAY_T_MIN && t1 < x->closest)
		set_cylinder_hits(cylinder, x, t1, i);
	if (d == 0)
		return (1);
	t2 = (-1 * quad.y + sqrt(d)) / (2 * quad.x);
	if (t2 > RAY_T_MIN && t2 < x->closest)
		set_cylinder_hits(cylinder, x, t2, i);
	return (2);
}

static void	set_cylinder(t_cylinder *cylinder)
{
	if (cylinder->p1.x == cylinder->p2.x && cylinder->p1.y == cylinder->p2.y &&
		cylinder->p1.z == cylinder->p2.z)
		cylinder->p2.y = cylinder->p1.y + 1;
	cylinder->p2 = rotate_vector(cylinder->p1, cylinder->p2, cylinder->rot);
	cylinder->axis = vector_minus(cylinder->p1, cylinder->p2);
	cylinder->axis = normalized_vector(cylinder->axis);
}

int			read_cyli(t_mlx *mlx, char *line)
{
	int		arr[13];

	int_array_set(arr, 13, 0);
	int_array_read(arr, 13, line);
	arr[7] = ft_int_clamp(arr[7], 0, 255);
	arr[8] = ft_int_clamp(arr[8], 0, 255);
	arr[9] = ft_int_clamp(arr[9], 0, 255);
	mlx->cylinders[mlx->cylinder_i].p1.x = ft_int_clamp_0(arr[0], -99, 99);
	mlx->cylinders[mlx->cylinder_i].p1.y = ft_int_clamp_0(arr[1], -99, 99);
	mlx->cylinders[mlx->cylinder_i].p1.z = ft_int_clamp_0(arr[2], -99, 99);
	mlx->cylinders[mlx->cylinder_i].p2.x = ft_int_clamp_0(arr[3], -99, 99);
	mlx->cylinders[mlx->cylinder_i].p2.y = ft_int_clamp_0(arr[4], -99, 99);
	mlx->cylinders[mlx->cylinder_i].p2.z = ft_int_clamp_0(arr[5], -99, 99);
	mlx->cylinders[mlx->cylinder_i].radius = ft_int_clamp(arr[6], 1, 99);
	mlx->cylinders[mlx->cylinder_i].color = arr[7]<<16 | arr[8]<<8 | arr[9];
	mlx->cylinders[mlx->cylinder_i].rot.x = ft_int_clamp_0(arr[10], -180, 180);
	mlx->cylinders[mlx->cylinder_i].rot.y = ft_int_clamp_0(arr[11], -180, 180);
	mlx->cylinders[mlx->cylinder_i].rot.z = ft_int_clamp_0(arr[12], -180, 180);
	set_cylinder(&mlx->cylinders[mlx->cylinder_i]);
	return (0);
}
