/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 12:58:52 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
*/

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
	quad.z = dot_vector(to_x, to_x) - cylinder.radius * cylinder.radius * dot_vector(cylinder.axis, cylinder.axis);

	d = double_sqr(quad.y) - 4 * quad.x * quad.z;
	if (d < 0.0)
		return (0);
	else if (d == 0)
	{
		t1 = (-1 * quad.y - sqrt(d)) / (2 * quad.x);
		return (1);
	}
	t1 = (-1 * quad.y - sqrt(d)) / (2 * quad.x);
	t2 = (-1 * quad.y + sqrt(d)) / (2 * quad.x);
	if (t1 > RAY_T_MIN && t1 < x->closest)
		x->closest = t1;
	else if (t2 > RAY_T_MIN && t2 < x->closest)
		x->closest = t2;
	if (x->closest == t1 || x->closest == t2)
	{
		x->color = cylinder.color;
		x->shape = CYLINDER;
		x->hit_index = i;
	}
	return (2);
}
