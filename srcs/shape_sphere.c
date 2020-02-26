/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/26 12:50:42 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
**	quadratic x would be "vector_length_pwr2(x->ray.direction);"
**	but it's normalized so we can use 1.
*/

static void	set_sphere_hit(t_sphere sphere, t_intersection *x, double d, int i)
{
	x->closest = d;
	x->color = sphere.color;
	x->shape = SPHERE;
	x->hit_index = i;
}

int			sphere_intersection(t_sphere sphere, t_intersection *x, int i)
{
	t_vector	to_sphere;
	t_vector	quadratic;
	double		d;

	to_sphere = vector_minus(x->ray.start, sphere.p);
	quadratic.x = 1;
	quadratic.y = 2 * dot_vector(x->ray.direction, to_sphere);
	quadratic.z = vector_length_pwr2(to_sphere) - double_sqr(sphere.radius);
	d = double_sqr(quadratic.y) - 4 * quadratic.x * quadratic.z;
	if (d < 0.0)
		return (0);
	x->t1 = (-1 * quadratic.y - sqrt(d)) / (2 * quadratic.x);
	if (x->t1 > RAY_T_MIN && x->t1 < x->closest)
		set_sphere_hit(sphere, x, x->t1, i);
	if (d == 0)
		return (1);
	x->t2 = (-1 * quadratic.y + sqrt(d)) / (2 * quadratic.x);
	if (x->t2 > RAY_T_MIN && x->t2 < x->closest)
		set_sphere_hit(sphere, x, x->t2, i);
	return (2);
}

int			read_sphere(t_mlx *mlx, char *line)
{
	int		arr[10];

	int_array_set(arr, 10, 0);
	int_array_read(arr, 10, line);
	arr[4] = ft_int_clamp(arr[4], 0, 255);
	arr[5] = ft_int_clamp(arr[5], 0, 255);
	arr[6] = ft_int_clamp(arr[6], 0, 255);
	mlx->spheres[mlx->sphere_i].p.x = ft_int_clamp_0(arr[0], -99, 99);
	mlx->spheres[mlx->sphere_i].p.y = ft_int_clamp_0(arr[1], -99, 99);
	mlx->spheres[mlx->sphere_i].p.z = ft_int_clamp_0(arr[2], -99, 99);
	mlx->spheres[mlx->sphere_i].radius = ft_int_clamp(arr[3], 1, 99);
	mlx->spheres[mlx->sphere_i].color = arr[4] << 16 | arr[5] << 8 | arr[6];
	mlx->spheres[mlx->sphere_i].rot.x = ft_int_clamp_0(arr[7], -180, 180);
	mlx->spheres[mlx->sphere_i].rot.y = ft_int_clamp_0(arr[8], -180, 180);
	mlx->spheres[mlx->sphere_i].rot.z = ft_int_clamp_0(arr[9], -180, 180);
	return (0);
}
