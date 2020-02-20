/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:35:28 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/19 15:40:42 by rjaakonm         ###   ########.fr       */
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
			sphere_intersection(mlx->spheres[i], &ix);
		if (i < mlx->plane_i)
			plane_intersection(mlx->planes[i], &ix);
		i++;
	}
	if (mlx->mouse_3 == 1)
	{
		ft_printf("\n*** CHECK X %d Y %d ***\n", x, y);
		ft_printf("distance to object: %f\n", ix.closest);
		ft_printf("hitpoint %.3f %.3f %.3f\n", ix.hitpoint.x, ix.hitpoint.y, ix.hitpoint.z);
		ft_printf("object color %#.6x\n", ix.color);
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
