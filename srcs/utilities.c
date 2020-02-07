/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:28:48 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/06 16:25:28 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

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
	perspective_cam(mlx->camera->origin, mlx->camera->target, mlx);
//	ft_printf("origin %f %f %f\n", mlx->camera.origin.x, mlx->camera.origin.y, mlx->camera.origin.z);
//	ft_printf("forward %f %f %f\n", mlx->camera.forward.x, mlx->camera.forward.y, mlx->camera.forward.z);
//	ft_printf("right %f %f %f\n", mlx->camera.right.x, mlx->camera.right.y, mlx->camera.right.z);
//	ft_printf("up %f %f %f\n", mlx->camera.up.x, mlx->camera.up.y, mlx->camera.up.z);
//	ft_printf("height %f width %f\n", mlx->camera.height, mlx->camera.width);
}

void		add_texts(t_mlx *mlx)
{
	char	str[6] = "testi\0";
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 30, 0xffffff,
		"MOVE CAMERA:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 50, 0xffffff,
		"Arrows, numpad +/-");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 70, 0xffffff,
		"EXIT: Esc");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 90, 0xffffff,
		str);
}
