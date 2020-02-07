/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:33:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/06 16:29:55 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	deal_keys(int key, t_mlx *mlx)
{
	if (key == 53)
		exit_free(mlx);
	if (key == 123)
	{
		mlx->camera->origin.x -= 0.1;
		mlx->camera->target.x -= 0.1;
	}
	if (key == 124)
	{
		mlx->camera->origin.x += .1;
		mlx->camera->target.x += .1;
	}
	if (key == 126)
	{
		mlx->camera->origin.y += 0.1;
		mlx->camera->target.y += 0.1;
	}
	if (key == 125)
	{
		mlx->camera->origin.y -= .1;
		mlx->camera->target.y -= .1;
	}
	if (key == 78)
	{
		mlx->camera->origin.z += 0.1;
		mlx->camera->target.z += 0.1;
	}
	if (key == 69)
	{
		mlx->camera->origin.z -= .1;
		mlx->camera->target.z += 0.1;
	}
//		ft_printf("cam origin %f %f %f\n", mlx->camera.origin.x, mlx->camera.origin.y, mlx->camera.origin.z);
//		ft_printf("cam target %f %f %f\n", mlx->camera.target.x, mlx->camera.target.y, mlx->camera.target.z);
	refresh(mlx);
}

int			deal_key(int key, t_mlx *mlx)
{
	ft_printf("%d <- key\n", key);
	if (key > 0 && key < 200)
		deal_keys(key, mlx);
	return (0);
}
