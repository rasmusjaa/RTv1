/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:33:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/21 13:15:17 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	deal_move_target(int key, t_mlx *mlx)
{
	if (key == 86)
		mlx->camera->target.x -= 1;
	else if (key == 88)
		mlx->camera->target.x += 1;
	else if (key == 91)
		mlx->camera->target.y += 1;
	else if (key == 84)
		mlx->camera->target.y -= 1;
	else if (key == 75)
		mlx->camera->target.z -= 1;
	else if (key == 67)
		mlx->camera->target.z += 1;
	refresh(mlx);
}

static void	deal_move_camera(int key, t_mlx *mlx)
{
	if (key == 123)
	{
		mlx->camera->origin = vector_minus(mlx->camera->origin, mlx->camera->right);
		mlx->camera->target = vector_minus(mlx->camera->target, mlx->camera->right);
	}
	else if (key == 124)
	{
		mlx->camera->origin = vector_plus(mlx->camera->origin, mlx->camera->right);
		mlx->camera->target = vector_plus(mlx->camera->target, mlx->camera->right);
	}
	else if (key == 126)
	{
		mlx->camera->origin.z -= 1;
		mlx->camera->target.z -= 1;
	}
	else if (key == 125)
	{
		mlx->camera->origin.z += 1;
		mlx->camera->target.z += 1;
	}
	else if (key == 78)
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

static void	deal_esc_exit(int key, t_mlx *mlx)
{
	if (key == 53)
		exit_free(mlx);
}

int			deal_key(int key, t_mlx *mlx)
{
	ft_printf("%d <- key\n", key);
	if ((key > 122 && key < 127) || key == 78 || key == 69)
		deal_move_camera(key, mlx);
	else if (key == 53)
		deal_esc_exit(key, mlx);
	else if (key == 86 || key == 88 || key == 91 || key == 84
			|| key == 75 || key == 67)
		deal_move_target(key, mlx);
	return (0);
}
