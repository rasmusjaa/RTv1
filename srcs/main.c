/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:23:37 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/05 17:36:09 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static void		copy_mlx(t_mlx *copy, t_mlx *mlx, int i)
{
	ft_memcpy(copy, mlx, sizeof(t_mlx));
	copy->thread = i;
}

void			multi_thread(t_mlx *mlx)
{
	pthread_t	*thread_group;
	t_mlx		*copies[THREADS];
	int			i;

	thread_group = malloc(sizeof(pthread_t) * THREADS);
	i = 0;
	while (i < THREADS)
	{
		copies[i] = (t_mlx *)malloc(sizeof(t_mlx));
		copy_mlx(copies[i], mlx, i);
		pthread_create(&thread_group[i], NULL, draw_view, copies[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(thread_group[i], NULL);
		free(copies[i]);
		i++;
	}
	free(thread_group);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
//	add_texts(mlx);
}

static void		mlx_values(t_mlx *mlx)
{
	mlx->img_width = IMG_WIDTH;
	mlx->img_height = IMG_HEIGHT;
	mlx->camera = perspective_cam(vector_0(), set_vector(0, 0, -1), mlx);
	ft_printf("origin %f %f %f\n", mlx->camera->origin.x, mlx->camera->origin.y, mlx->camera->origin.z);
	ft_printf("forward %f %f %f\n", mlx->camera->forward.x, mlx->camera->forward.y, mlx->camera->forward.z);
	ft_printf("right %f %f %f\n", mlx->camera->right.x, mlx->camera->right.y, mlx->camera->right.z);
	ft_printf("up %f %f %f\n", mlx->camera->up.x, mlx->camera->up.y, mlx->camera->up.z);
	ft_printf("height %f width %f\n", mlx->camera->height, mlx->camera->width);
}

static int		mlx_start(t_mlx	*mlx)
{
	mlx_values(mlx);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOW_X, WINDOW_Y, "RTv1");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOW_X, WINDOW_Y);
	mlx->data_addr = mlx_get_data_addr(mlx->img_ptr,
		&mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx->bpp /= 8;
	multi_thread(mlx);
	mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);
/*	mlx_hook(mlx->win_ptr, 4, 0, mouse_press, mlx);
	mlx_hook(mlx->win_ptr, 5, 0, mouse_release, mlx);
	mlx_hook(mlx->win_ptr, 6, 0, mouse_move, mlx);*/
	mlx_hook(mlx->win_ptr, 17, 0, exit_free, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

int				main(void)
{
	t_mlx	*mlx;
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (1);
	mlx_start(mlx);
	return (0);
}
/*
vektorit:
add
substract
normalize

muodoilla:
position
rotation
scale / radius
color

valoilla:
type
position
direction (point lightilla, ei auringolla)
color
intensity
*/

// optimointiin tsekkaa does intersect joka muodosta ja lopeta loop jos edes 1
