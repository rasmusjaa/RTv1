/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:41:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/24 15:48:43 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

/*
**	returns number of touches, for later use: t1 first touch t2 second
*/

int			cylinder_intersection(t_cylinder cylinder, t_intersection *x, int i)
{
	t_vector	to_cylinder;
	t_vector	quadratic;
	double		t1;
	double		t2;
	double		d;

	to_cylinder = vector_minus(x->ray.start, cylinder.p1);
	quadratic.x = vector_length_pwr2(x->ray.direction);
	quadratic.y = 2 * dot_vector(x->ray.direction, to_cylinder);
	quadratic.z = vector_length_pwr2(to_cylinder) - double_sqr(cylinder.radius);
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
