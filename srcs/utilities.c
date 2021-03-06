/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:28:48 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/03/05 17:44:32 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		exit_message(char *str)
{
	ft_putendl(str);
	exit(0);
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
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 90, 0xffffff,
		"CAMERA TARGET: asdwqe");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 130, 0xffffff,
		"EXIT: Esc");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 810, 0xffffff,
		"CAMERA POSITION");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 890, 0xffffff,
		"CAMERA TARGET");
	add_texts_2(mlx);
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
	return (vector_plus(target, origin));
}
