/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/24 18:40:51 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
*/

int			cone_intersection(t_cone cone, t_intersection *x, int i)
{
	t_vector	to_cone;
	t_vector	quad;
	double		t1;
	double		t2;
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
	t1 = (-1 * quad.y - sqrt(d)) / (2 * quad.x);
	t2 = (-1 * quad.y + sqrt(d)) / (2 * quad.x);
	d = t1 < t2 ? t1 : t2;
	if (d > RAY_T_MIN && d < x->closest)
	{
		x->closest = d;
		x->color = cone.color;
		x->shape = CONE;
		x->hit_index = i;
	}
	if (t1 == t2)
		return (1);
	return (2);
}
