/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:33:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/26 12:17:17 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	deal_move_camera2(int key, t_mlx *mlx)
{
	if (key == 78)
	{
		mlx->camera->origin.y -= 1;
		mlx->camera->target.y -= 1;
	}
	else if (key == 69)
	{
		mlx->camera->origin.y += 1;
		mlx->camera->target.y += 1;
	}
	refresh(mlx);
}

static void	deal_move_camera(int key, t_mlx *mlx)
{
	t_camera	*cam;

	cam = mlx->camera;
	if (key == 123)
	{
		cam->origin = vector_minus(cam->origin, cam->right);
		cam->target = vector_minus(cam->target, cam->right);
	}
	else if (key == 124)
	{
		cam->origin = vector_plus(cam->origin, cam->right);
		cam->target = vector_plus(cam->target, cam->right);
	}
	else if (key == 126)
	{
		cam->origin = vector_plus(cam->origin, cam->forward);
		cam->target = vector_plus(cam->target, cam->forward);
	}
	else if (key == 125)
	{
		cam->origin = vector_minus(cam->origin, cam->forward);
		cam->target = vector_minus(cam->target, cam->forward);
	}
	refresh(mlx);
}

static void	deal_esc_exit(int key, t_mlx *mlx)
{
	if (key == 53)
		exit_free(mlx);
}

int			deal_key(int key, t_mlx *mlx)
{
	ft_printf("You pressed key: %d\n", key);
	if (key > 122 && key < 127)
		deal_move_camera(key, mlx);
	else if (key == 78 || key == 69)
		deal_move_camera2(key, mlx);
	else if (key == 53)
		deal_esc_exit(key, mlx);
	return (0);
}
