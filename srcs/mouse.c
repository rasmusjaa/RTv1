/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:37:11 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/21 15:12:55 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int			mouse_move(int x, int y, t_mlx *mlx)
{

	if (mlx->mouse_1 == 1)
	{
		mlx->camera->rot.y -= (mlx->mouse_x - x) / 20.0;
		mlx->camera->rot.x += (mlx->mouse_y - y) / 20.0;
		refresh(mlx);
	}
	else if (mlx->mouse_2 == 1)
	{
		refresh(mlx);
	}
	/*
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

static void	mouse_wheel(int button, int x, int y, t_mlx *mlx)
{
	if (button == 3)
		mlx->mouse_3 = 1;
	if (x >= 0 && y >= 0 && x < IMG_WIDTH && y < IMG_HEIGHT)
		get_color(x, y, mlx);
	mlx->mouse_3 = 0;

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
		mouse_wheel(button, x, y, mlx);
//	refresh(mlx);
	return (0);
}
