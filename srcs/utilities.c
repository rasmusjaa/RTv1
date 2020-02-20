/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:28:48 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/19 13:53:52 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

// void		read_scene(t_mlx *mlx);

void		refresh(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOW_X, WINDOW_Y);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	multi_thread(mlx);
}

int			exit_free(t_mlx *mlx)
{
	free(mlx->camera);
	free(mlx->scene);
	free(mlx);
	exit(0);
}

void		set_objects(t_mlx *mlx)
{
	if (mlx->camera->origin.x == mlx->camera->target.x &&
		mlx->camera->origin.y == mlx->camera->target.y &&
		mlx->camera->origin.z == mlx->camera->target.z)
	mlx->camera->target.z = mlx->camera->origin.z - 1;
	perspective_cam(mlx->camera->origin, mlx->camera->target, mlx);
//	ft_printf("forward %f %f %f\n", mlx->camera.forward.x, mlx->camera.forward.y, mlx->camera.forward.z);
//	ft_printf("right %f %f %f\n", mlx->camera.right.x, mlx->camera.right.y, mlx->camera.right.z);
//	ft_printf("up %f %f %f\n", mlx->camera.up.x, mlx->camera.up.y, mlx->camera.up.z);
//	ft_printf("height %f width %f\n", mlx->camera.height, mlx->camera.width);
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
