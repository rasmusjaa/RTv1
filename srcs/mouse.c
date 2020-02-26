/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:37:11 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/26 12:40:11 by rjaakonm         ###   ########.fr       */
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
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	return (0);
}

int			mouse_release(int button, int x, int y, t_mlx *mlx)
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
}

int			mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == 1)
		mlx->mouse_1 = 1;
	else if (button == 2)
		mlx->mouse_2 = 1;
	else if (button == 3)
		mouse_wheel(button, x, y, mlx);
	return (0);
}
