/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:29:43 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/03 19:18:10 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int			plane_intersection(t_plane plane, t_intersection x)
{
	double	dot;
	double	d;

	dot = dot_vector(x.ray.direction, plane.normal);
	if (dot == 0.0)
		return (0);
	d = dot_vector(vector_minus(plane.p, x.ray.start), plane.normal);
	if (d <= RAY_T_MIN || d >= RAY_T_MAX)
		return (0);
	x.d = d;
	x.shape = PLANE;
	return (1);
}
