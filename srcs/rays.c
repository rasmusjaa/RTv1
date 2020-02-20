/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:37:33 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/07 17:12:04 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_ray	set_ray(t_point start, t_vector direction)
{
	t_ray	ray;

	ray.start = start;
	ray.direction = direction;
	ray.t_max = RAY_T_MAX;
	return (ray);
}

t_ray	copy_ray(t_ray ray1)
{
	t_ray	ray2;

	ray2.start = ray1.start;
	ray2.direction = ray1.direction;
	ray2.t_max = ray1.t_max;
	return (ray2);
}

t_point	ray_point(t_ray ray, double d)
{
	t_point	point;

	point.x = d * ray.direction.x + ray.start.x;
	point.y = d * ray.direction.y + ray.start.y;
	point.z = d * ray.direction.z + ray.start.z;
	return (point);
}
