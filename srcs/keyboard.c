/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:33:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/07 16:15:14 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void	deal_numpad_245680(int key, t_mlx *mlx)
{
	if (key == 86)
	{
		mlx->camera->target.x -= 1;
	}
	else if (key == 88)
	{
		mlx->camera->target.x += 1;
	}
	else if (key == 91)
	{
		mlx->camera->target.y += 1;
	}
	else if (key == 84)
	{
		mlx->camera->target.y -= 1;
	}
	else if (key == 87)
	{
		mlx->camera->origin.y -= 0.1;
		mlx->camera->target.y -= 0.1;
	}
	else if (key == 82)
	{
		mlx->camera->origin.x = 0;
		mlx->camera->origin.y = 0;
		mlx->camera->origin.z = 0;
		mlx->camera->target.x = mlx->camera->origin.x;
		mlx->camera->target.y = mlx->camera->origin.y;
		mlx->camera->target.z = mlx->camera->origin.z - 1;
	}
	refresh(mlx);
}

static void	deal_arrows(int key, t_mlx *mlx)
{
	if (key == 123)
	{
		mlx->camera->origin.x -= 0.1;
		mlx->camera->target.x -= 0.1;
	}
	else if (key == 124)
	{
		mlx->camera->origin.x += 0.1;
		mlx->camera->target.x += 0.1;
	}
	else if (key == 126)
	{
		mlx->camera->origin.y += 0.1;
		mlx->camera->target.y += 0.1;
	}
	else if (key == 125)
	{
		mlx->camera->origin.y -= 0.1;
		mlx->camera->target.y -= 0.1;
	}
	refresh(mlx);
}

static void	deal_esc_plus_minus(int key, t_mlx *mlx)
{
	if (key == 53)
		exit_free(mlx);
	else if (key == 78)
	{
		mlx->camera->origin.z += 0.1;
		mlx->camera->target.z += 0.1;
	}
	else if (key == 69)
	{
		mlx->camera->origin.z -= 0.1;
		mlx->camera->target.z -= 0.1;
	}
	refresh(mlx);
}

int			deal_key(int key, t_mlx *mlx)
{
	ft_printf("%d <- key\n", key);
	if (key > 122 && key < 127)
		deal_arrows(key, mlx);
	else if (key == 53 || key == 78 || key == 69)
		deal_esc_plus_minus(key, mlx);
	else if (key == 86 || key == 88 || key == 91 || key == 84 || key == 87 || key == 82)
		deal_numpad_245680(key, mlx);
	return (0);
}
