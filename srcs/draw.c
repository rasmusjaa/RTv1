/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:35:28 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/26 12:02:06 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	image_set(int x, int y, t_mlx *mlx, int color)
{
	*(int*)(mlx->data_addr + (((y * WINDOW_X) + x)
		* mlx->bpp)) = color;
}

void		set_hit_normal(t_mlx *mlx, t_intersection *x)
{
	x->hitpoint = ray_point(x->ray, x->closest);
	if (x->shape == SPHERE)
		x->hitnormal = normalized_vector(vector_minus(x->hitpoint,
			mlx->spheres[x->hit_index].p));
	else if (x->shape == PLANE)
		x->hitnormal = mlx->planes[x->hit_index].normal;
	else if (x->shape == CYLINDER)
		set_cylinder_normal(mlx, x);
	else if (x->shape == CONE)
	{
		x->hitnormal = vector_minus(x->hitpoint, mlx->cones[x->hit_index].p1);
		x->hitnormal = vector_divide_nb(vector_multiply_nb(x->hitnormal,
			dot_vector(mlx->cones[x->hit_index].axis, x->hitnormal)),
			dot_vector(x->hitnormal, x->hitnormal));
		x->hitnormal = vector_minus(mlx->cones[x->hit_index].axis,
			x->hitnormal);
		x->hitnormal = normalized_vector(x->hitnormal);
	}
}

int			get_color(int x, int y, t_mlx *mlx)
{
	t_vector		target;
	t_ray			ray;
	t_intersection	ix;
	int				i;

	target.x = 2.0 * x / (mlx->img_width - 1) - 1.0;
	target.y = -2.0 * y / (mlx->img_height - 1) + 1;
	ray = camera_ray(mlx->camera, target);
	ix = get_intersection(ray, mlx);
	i = 0;
	while (i < 10)
	{
		if (i < mlx->sphere_i)
			sphere_intersection(mlx->spheres[i], &ix, i);
		if (i < mlx->plane_i)
			plane_intersection(mlx->planes[i], &ix, i);
		if (i < mlx->cylinder_i)
			cylinder_intersection(mlx->cylinders[i], &ix, i);
		if (i < mlx->cone_i)
			cone_intersection(mlx->cones[i], &ix, i);
		i++;
	}
	set_hit_normal(mlx, &ix);
	ray_color(mlx, &ix);
	return (ix.color);
}

void		*draw_view(void *data)
{
	int		y;
	int		x;
	int		color;
	t_mlx	*mlx;

	mlx = (t_mlx *)data;
	color = mlx->scene->ambient;
	y = mlx->thread;
	while (y < mlx->img_height)
	{
		x = 0;
		while (x < mlx->img_width)
		{
			color = get_color(x, y, mlx);
			image_set(x, y, mlx, color);
			x++;
		}
		y += THREADS;
	}
	return (data);
}
