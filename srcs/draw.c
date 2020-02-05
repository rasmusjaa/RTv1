/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:35:28 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/05 17:48:41 by rjaakonm         ###   ########.fr       */
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
	sphere.color = 0xffffff;

	t_intersection ix;

	ix = get_intersection(ray);

	if (sphere_intersection(sphere, &ix) != 0)
	{
		return (sphere.color);
	}
	return (0x000000);
}

void		*draw_view(void *data)
{
	int		y;
	int		x;
	int		color;
	t_mlx	*mlx;

	mlx = (t_mlx *)data;

	color = 0x000000;
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
