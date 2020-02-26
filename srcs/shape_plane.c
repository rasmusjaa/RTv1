/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:29:43 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/26 12:44:15 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int			plane_intersection(t_plane plane, t_intersection *x, int i)
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
		x->color = plane.color;
		x->shape = PLANE;
		x->hit_index = i;
	}
	return (1);
}

static void	set_plane(t_plane *plane)
{
	if (plane->p.x == plane->normal.x && plane->p.y == plane->normal.y &&
		plane->p.z == plane->normal.z)
		plane->normal.y = plane->p.y + 1;
	plane->normal = rotate_vector(plane->p, plane->normal, plane->rot);
	plane->normal = vector_minus(plane->normal, plane->p);
	plane->normal = normalized_vector(plane->normal);
}

int			read_plane(t_mlx *mlx, char *line)
{
	int		arr[12];

	int_array_set(arr, 12, 0);
	int_array_read(arr, 12, line);
	arr[6] = ft_int_clamp(arr[6], 0, 255);
	arr[7] = ft_int_clamp(arr[7], 0, 255);
	arr[8] = ft_int_clamp(arr[8], 0, 255);
	mlx->planes[mlx->plane_i].p.x = ft_int_clamp_0(arr[0], -99, 99);
	mlx->planes[mlx->plane_i].p.y = ft_int_clamp_0(arr[1], -99, 99);
	mlx->planes[mlx->plane_i].p.z = ft_int_clamp_0(arr[2], -99, 99);
	mlx->planes[mlx->plane_i].normal.x = ft_int_clamp_0(arr[3], -99, 99);
	mlx->planes[mlx->plane_i].normal.y = ft_int_clamp_0(arr[4], -99, 99);
	mlx->planes[mlx->plane_i].normal.z = ft_int_clamp_0(arr[5], -99, 99);
	mlx->planes[mlx->plane_i].color = arr[6] << 16 | arr[7] << 8 | arr[8];
	mlx->planes[mlx->plane_i].rot.x = ft_int_clamp_0(arr[9], -180, 180);
	mlx->planes[mlx->plane_i].rot.y = ft_int_clamp_0(arr[10], -180, 180);
	mlx->planes[mlx->plane_i].rot.z = ft_int_clamp_0(arr[11], -180, 180);
	set_plane(&mlx->planes[mlx->plane_i]);
	return (0);
}
