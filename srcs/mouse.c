/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:37:11 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/07 15:59:30 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int			mouse_move(int x, int y, t_mlx *mlx)
{
/*	if (mlx->mouse_1 == 1)
	{
		mlx->move_x -= mlx->mouse_x - x;
		mlx->move_y -= mlx->mouse_y - y;
		refresh(mlx);
	}
	else if (mlx->mouse_2 == 1)
	{
		mlx->color_x -= mlx->mouse_x - x;
		mlx->color_x -= mlx->mouse_y - y;
		if (mlx->color_x < 1 || mlx->color_x > 10000)
			mlx->color_x = 1;
		refresh(mlx);
	}
	else if (mlx->mousemove == 1)
	{
		mlx->z_r -= (float)(mlx->mouse_x - x) / 200;
		mlx->z_i -= (float)(mlx->mouse_y - y) / 200;
		refresh(mlx);
	}*/
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	return (0);
}

int			mouse_release(int button, int x, int y,  t_mlx *mlx)
{
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (button == 1)
		mlx->mouse_1 = 0;
	else if (button == 2)
		mlx->mouse_2 = 0;
	return (0);
}

static void	mouse_press2(int button, int x, int y, t_mlx *mlx)
{
	if (button == 1)
		mlx->mouse_1 = 1;

	t_vector	target;
	t_ray		ray;

	target.x = 2.0 * x / (mlx->img_width - 1) - 1.0;
	target.y = -2.0 * y / (mlx->img_height - 1) + 1;

	ray = camera_ray(mlx->camera, target);

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

	t_intersection ix;

	ix = get_intersection(ray, mlx);

	sphere_intersection(sphere, &ix);
	sphere_intersection(sphere2, &ix);
	ft_printf("distance to object: %f\n", ix.closest);
	ft_printf("color %#.6x\n", ix.color);
/*	mlx->move_x -= (x - mlx->img_width / 2);
	mlx->move_y -= (y - mlx->img_height / 2);
	if (button == 4)
	{
		mlx->zoom *= 1.2;
		mlx->move_x *= 1.2;
		mlx->move_y *= 1.2;
		mlx->move_x += (x - mlx->img_width / 2);
		mlx->move_y += (y - mlx->img_height / 2);
	}
	if (button == 5)
	{
		mlx->zoom *= 0.8;
		mlx->move_x *= 0.8;
		mlx->move_y *= 0.8;
		mlx->move_x += (x - mlx->img_width / 2);
		mlx->move_y += (y - mlx->img_height / 2);
	} */
}

int			mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == 1)
		mlx->mouse_1 = 1;
	else if (button == 2)
		mlx->mouse_2 = 1;
	else if (button == 3 || button == 4 || button == 5)
		mouse_press2(button, x, y, mlx);
//	refresh(mlx);
	return (0);
}
