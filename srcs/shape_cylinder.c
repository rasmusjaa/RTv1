/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/21 19:16:04 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
*/

int			cylinder_intersection(t_cylinder cylinder, t_intersection *x)
{
	t_ray		ray;
	t_vector	quadratic;
	double		t1;
	double		t2;
	double		d;

	ray = copy_ray(x->ray);
	ray.start = vector_minus(x->ray.start, cylinder.p1);
	quadratic.x = vector_length_pwr2(ray.direction);
	quadratic.y = 2 * dot_vector(ray.direction, ray.start);
	quadratic.z = vector_length_pwr2(ray.start) - double_sqr(cylinder.radius);
	d = double_sqr(quadratic.y) - 4 * quadratic.x * quadratic.z;

	if (d < 0.0)
		return (0);
	else if (d == 0)
	{
		t1 = (-1 * quadratic.y - sqrt(d)) / (2 * quadratic.x);
		return (1);
	}
	t1 = (-1 * quadratic.y - sqrt(d)) / (2 * quadratic.x);
	t2 = (-1 * quadratic.y + sqrt(d)) / (2 * quadratic.x);
	if (t1 > RAY_T_MIN && t1 < x->closest)
	{
		x->closest = t1;
		x->hitpoint = ray_point(x->ray, t1);
		x->hitnormal = normalized_vector(vector_minus(x->hitpoint, cylinder.p1));
		x->color = cylinder.color;
		x->shape = CYLINDER;
	}
	else if (t2 > RAY_T_MIN && t2 < x->closest)
	{
		x->closest = t2;
		x->hitpoint = ray_point(x->ray, t2);
		x->hitnormal = normalized_vector(vector_minus(x->hitpoint, cylinder.p1));
		x->color = cylinder.color;
		x->shape = CYLINDER;
	}
	return (2);
}
