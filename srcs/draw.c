/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:35:28 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/06 16:18:44 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	image_set(int x, int y, t_mlx *mlx, int color)
{
	*(int*)(mlx->data_addr + (((y * WINDOW_X) + x)
		* mlx->bpp)) = color;
}

int		get_color(int x, int y, t_mlx *mlx)
{
	t_vector	target;
	t_ray		ray;

	target.x = 2.0 * x / (mlx->img_width - 1) - 1.0;
	target.y = -2.0 * y / (mlx->img_height - 1) + 1;

	ray = camera_ray(mlx->camera, target);

// loop ray against all shapes
	t_sphere	sphere;
	sphere.radius = 2;
	sphere.p.x = 0;
	sphere.p.y = 0;
	sphere.p.z = -5;
	sphere.color = 0x0000ff;

	t_sphere	sphere2;
	sphere2.radius = 1;
	sphere2.p.x = 0;
	sphere2.p.y = 0;
	sphere2.p.z = -3;
	sphere2.color = 0x00ff00;

	t_plane		plane;
	plane.p = set_vector(0, -1, 0);
	plane.normal = set_vector(0, 1 ,0);
	plane.color = 0xff0000;

	t_intersection ix;

	ix = get_intersection(ray, mlx);

	sphere_intersection(sphere, &ix);
	sphere_intersection(sphere2, &ix);
	plane_intersection(plane, &ix);
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
