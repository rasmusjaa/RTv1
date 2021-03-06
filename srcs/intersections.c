/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:37:33 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/24 14:58:41 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_intersection	copy_intersection(t_intersection x1)
{
	t_intersection	x2;

	x2.ray = x1.ray;
	x2.d = x1.d;
	x2.shape = x1.shape;
	return (x2);
}

t_intersection	get_intersection(t_ray ray, t_mlx *mlx)
{
	t_intersection	x;

	x.ray = ray;
	x.shape = 0;
	x.hit_index = 0;
	x.closest = 1000;
	x.color = mlx->scene->ambient;
	return (x);
}

int				intersected(t_intersection x)
{
	return (x.shape);
}

t_point			intersect_pos(t_intersection x, t_ray ray, double d)
{
	t_point			point;

	x.closest = x.closest;
	point = ray_point(ray, d);
	return (point);
}
