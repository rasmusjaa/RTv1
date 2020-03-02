/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:23:37 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/03/02 14:27:27 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

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
		ft_memcpy(copies[i], mlx, sizeof(t_mlx));
		copies[i]->thread = i;
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
	add_texts(mlx);
}

static void		mlx_values(t_mlx *mlx)
{
	mlx->img_width = IMG_WIDTH;
	mlx->img_height = IMG_HEIGHT;
	mlx->sphere_i = 0;
	mlx->plane_i = 0;
	mlx->cylinder_i = 0;
	mlx->cone_i = 0;
	mlx->spot_i = 0;
	mlx->camera->origin = set_vector(0, 0, 0);
	mlx->camera->target = set_vector(0, 0, -1);
	mlx->scene->ambient = 0x000000;
	mlx->scene->speculars = 0;
	mlx->scene->shadows = 0;
	mlx->scene->shading = 0;
	mlx->scene->ambient_r = 0;
	mlx->scene->ambient_g = 0;
	mlx->scene->ambient_b = 0;
}

static int		handle_expose(void *mlx2)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx2;
	mlx->sphere_i = 0;
	mlx->plane_i = 0;
	mlx->cylinder_i = 0;
	mlx->cone_i = 0;
	mlx->spot_i = 0;
	mlx->scene->ambient = 0x000000;
	mlx->scene->speculars = 0;
	mlx->scene->shadows = 0;
	mlx->scene->shading = 0;
	mlx->scene->ambient_r = 0;
	mlx->scene->ambient_g = 0;
	mlx->scene->ambient_b = 0;
	read_scene((t_mlx *)mlx);
	return (0);
}

static int		mlx_start(t_mlx *mlx)
{
	mlx_values(mlx);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOW_X, WINDOW_Y, "RTv1");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOW_X, WINDOW_Y);
	mlx->data_addr = mlx_get_data_addr(mlx->img_ptr,
		&mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx->bpp /= 8;
	read_scene(mlx);
	mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);
	mlx_hook(mlx->win_ptr, 4, 0, mouse_press, mlx);
	mlx_hook(mlx->win_ptr, 5, 0, mouse_release, mlx);
	mlx_hook(mlx->win_ptr, 6, 0, mouse_move, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, exit_free, mlx);
	mlx_expose_hook(mlx->win_ptr, handle_expose, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

int				main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2 || ft_strncmp(av[1], "scene_", 6) != 0)
	{
		ft_putendl("usage: ./RTv1 [scene_#]");
		exit(0);
	}
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (1);
	if (!(mlx->camera = (t_camera *)malloc(sizeof(t_camera))))
		return (1);
	if (!(mlx->scene = (t_scene *)malloc(sizeof(t_scene))))
		return (1);
	mlx->scene->name = av[1];
	mlx_start(mlx);
	return (0);
}
