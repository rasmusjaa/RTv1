/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:29:43 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/10 13:05:15 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int			plane_intersection(t_plane plane, t_intersection *x)
{
	double	dot;
	double	t;

	dot = dot_vector(x->ray.direction, plane.normal);
	if (dot == 0.0)
		return (0);
	t = dot_vector(vector_minus(plane.p, x->ray.start), plane.normal) / dot;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX)
		return (0);
	if (t < x->closest)
	{
		x->closest = t;
		x->hitpoint = ray_point(x->ray, t);
		x->hitnormal = plane.normal;
		x->color = plane.color;
		x->shape = PLANE;
	}
	return (1);
}
