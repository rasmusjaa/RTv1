/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:28:48 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 18:06:29 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		exit_message(char *str)
{
	ft_putendl(str);
	exit (0);
}

void		refresh(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOW_X, WINDOW_Y);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	set_camera(mlx);
	multi_thread(mlx);
}

int			exit_free(t_mlx *mlx)
{
	free(mlx->camera);
	free(mlx->scene);
	free(mlx);
	exit(0);
}

void		add_texts(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 30, 0xffffff,
		"MOVE CAMERA:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 50, 0xffffff,
		"Arrows, Numpad +-");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 70, 0xffffff,
		"MOVE TARGET:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 90, 0xffffff,
		"Numpad 2468 */");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 110, 0xffffff,
		"EXIT: Esc");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 810, 0xffffff,
		"CAMERA POSITION");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 830, 0xffffff,
		ft_itoa((int)mlx->camera->origin.x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 850, 0xffffff,
		ft_itoa((int)mlx->camera->origin.y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 870, 0xffffff,
		ft_itoa((int)mlx->camera->origin.z));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 890, 0xffffff,
		"CAMERA TARGET");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 910, 0xffffff,
		ft_itoa((int)mlx->camera->target.x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 930, 0xffffff,
		ft_itoa((int)mlx->camera->target.y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 950, 0xffffff,
		ft_itoa((int)mlx->camera->target.z));
}

t_vector	rotate_vector(t_vector origin, t_vector target, t_vector rot)
{
	t_vector	temp;

	target = vector_minus(target, origin);
	if (rot.x != 0)
	{
		rot.x *= -1 * M_PI / 180.0;
		temp.y = target.y;
		target.y = target.y * cos(rot.x) + target.z * sin(rot.x);
		target.z = -1 * temp.y * sin(rot.x) + target.z * cos(rot.x);
	}
	if (rot.y != 0)
	{
		rot.y *= -1 * M_PI / 180.0;
		temp.x = target.x;
		target.x = target.x * cos(rot.y) + target.z * sin(rot.y);
		target.z = -1 * temp.x * sin(rot.y) + target.z * cos(rot.y);
	}
	if (rot.z != 0)
	{
		rot.z *= -1 * M_PI / 180.0;
		temp.x = target.x;
		target.x = target.x * cos(rot.z) - target.y * sin(rot.z);
		target.y = temp.x * sin(rot.z) + target.y * cos(rot.z);
	}
	target = vector_plus(target, origin);
	return (target);
}
