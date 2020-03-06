/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:42:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/03/06 15:52:02 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		add_texts_2(t_mlx *mlx)
{
	char	*str;

	str = ft_rprintf("%.2f", mlx->camera->origin.x);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 830, 0xffffff, str);
	free(str);
	str = ft_rprintf("%.2f", mlx->camera->origin.y);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 850, 0xffffff, str);
	free(str);
	str = ft_rprintf("%.2f", mlx->camera->origin.z);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 870, 0xffffff, str);
	free(str);
	str = ft_rprintf("%.2f", mlx->camera->target.x);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 910, 0xffffff, str);
	free(str);
	str = ft_rprintf("%.2f", mlx->camera->target.y);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 930, 0xffffff, str);
	free(str);
	str = ft_rprintf("%.2f", mlx->camera->target.z);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1015, 950, 0xffffff, str);
	free(str);
}
