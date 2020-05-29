/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_linux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:33:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/05/29 21:03:49 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	deal_move_camera3(int key, t_mlx *mlx)
{
	if (key == 119)
		mlx->camera->target.z += 1;
	else if (key == 115)
		mlx->camera->target.z -= 1;
	else if (key == 97)
		mlx->camera->target.x -= 1;
	else if (key == 100)
		mlx->camera->target.x += 1;
	refresh(mlx);
}

static void	deal_move_camera2(int key, t_mlx *mlx)
{
	if (key == 65453)
	{
		mlx->camera->origin.y -= 1;
		mlx->camera->target.y -= 1;
	}
	else if (key == 65451)
	{
		mlx->camera->origin.y += 1;
		mlx->camera->target.y += 1;
	}
	else if (key == 113)
		mlx->camera->target.y -= 1;
	else if (key == 101)
		mlx->camera->target.y += 1;
	refresh(mlx);
}

static void	deal_move_camera(int key, t_mlx *mlx)
{
	t_camera	*cam;

	cam = mlx->camera;
	if (key == 65361)
	{
		cam->origin = vector_minus(cam->origin, cam->right);
		cam->target = vector_minus(cam->target, cam->right);
	}
	else if (key == 65363)
	{
		cam->origin = vector_plus(cam->origin, cam->right);
		cam->target = vector_plus(cam->target, cam->right);
	}
	else if (key == 65362)
	{
		cam->origin = vector_plus(cam->origin, cam->forward);
		cam->target = vector_plus(cam->target, cam->forward);
	}
	else if (key == 65364)
	{
		cam->origin = vector_minus(cam->origin, cam->forward);
		cam->target = vector_minus(cam->target, cam->forward);
	}
	refresh(mlx);
}

static void	deal_esc_exit(int key, t_mlx *mlx)
{
	if (key == 65307)
		exit_free(mlx);
}

int			deal_key(int key, t_mlx *mlx)
{
	ft_printf("You pressed key: %d\n", key);
	if (key > 65360 && key < 65365)
		deal_move_camera(key, mlx);
	else if (key == 65453 || key == 65451 || key == 113 || key == 101)
		deal_move_camera2(key, mlx);
	else if (key == 119 || key == 97 || key == 115 || key == 100)
		deal_move_camera3(key, mlx);
	else if (key == 65307)
		deal_esc_exit(key, mlx);
	return (0);
}
