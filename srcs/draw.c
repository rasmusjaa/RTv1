/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:35:28 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/24 18:57:35 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	image_set(int x, int y, t_mlx *mlx, int color)
{
	*(int*)(mlx->data_addr + (((y * WINDOW_X) + x)
		* mlx->bpp)) = color;
}

void		set_hit(t_mlx *mlx, t_intersection *x)
{
	x->hitpoint = ray_point(x->ray, x->closest);
	if (x->shape == SPHERE)
	{
		x->hitnormal = normalized_vector(vector_minus(x->hitpoint,
			mlx->spheres[x->hit_index].p));
	}
	else if (x->shape == PLANE)
	{
		x->hitnormal = mlx->planes[x->hit_index].normal;
	}
	else if (x->shape == CYLINDER)
	{
		x->hitnormal = normalized_vector(vector_minus(x->hitpoint,
			mlx->cylinders[x->hit_index].p1));
	}
	else if (x->shape == CONE)
	{
		x->hitnormal = vector_minus(x->hitpoint, mlx->cones[x->hit_index].p1);
		x->hitnormal = vector_divide_nb(vector_multiply_nb(x->hitnormal,
			dot_vector(mlx->cones[x->hit_index].axis, x->hitnormal)),
			dot_vector(x->hitnormal, x->hitnormal));
		x->hitnormal = vector_minus(x->hitnormal, mlx->cones[x->hit_index].axis);

		// t_vector	coned =
		// vector_minus(mlx->cones[x->hit_index].p1, mlx->cones[x->hit_index].p2);
		// t_vector	hit_cone =
		// vector_minus(x->hitpoint, mlx->cones[x->hit_index].p1);
		// x->hitnormal = vector_minus(hit_cone,
		// 	vector_multiply_nb(coned, vector_length(hit_cone) / cos(10 * M_PI / 180.0))
		// 	);
		x->hitnormal = normalized_vector(x->hitnormal);
	}
}

int		get_color(int x, int y, t_mlx *mlx)
{
	t_vector	target;
	t_ray		ray;
	t_intersection ix;
	int		i;

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
	set_hit(mlx, &ix);
	if (mlx->mouse_3 == 1)
	{
		ft_printf("\n*** CHECK X %d Y %d ***\n", x, y);
		ft_printf("distance to object: %f\n", ix.closest);
		ft_printf("hitpoint %.3f %.3f %.3f\n", ix.hitpoint.x, ix.hitpoint.y, ix.hitpoint.z);
		ft_printf("object %d color %#.6x\n", ix.shape, ix.color);
		ft_printf("\n*** CONE ***\n");
		ft_printf("x %f y %f z %f\n", mlx->cones[0].p1.x, mlx->cones[0].p1.y, mlx->cones[0].p1.z);
		ft_printf("x %f y %f z %f\n", mlx->cones[0].p2.x, mlx->cones[0].p2.y, mlx->cones[0].p2.z);
	}
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
