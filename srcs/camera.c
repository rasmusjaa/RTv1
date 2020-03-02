/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:18:45 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/03/02 14:28:08 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		perspective_cam(t_point origin, t_vector target, t_mlx *mlx)
{
	t_camera	*camera;
	t_vector	up;
	double		aspect_ratio;

	camera = mlx->camera;
	aspect_ratio = mlx->img_width / mlx->img_height;
	camera->origin = origin;
	camera->forward = normalized_vector(vector_minus(target, origin));
	up = vector_y();
	camera->right = normalized_vector(cross_vector(camera->forward, up));
	camera->up = normalized_vector(cross_vector(camera->right,
		camera->forward));
	camera->height = tan((FOV * M_PI / 180.0) / 2);
	camera->width = camera->height * aspect_ratio;
}

t_ray		camera_ray(t_camera *camera, t_point target)
{
	t_ray		ray;
	t_vector	v1;
	t_vector	v2;

	ray.start = copy_vector(camera->origin);
	ray.direction = copy_vector(camera->forward);
	v1 = vector_multiply_nb(camera->right, (target.x * camera->width));
	v2 = vector_multiply_nb(camera->up, (target.y * camera->height));
	ray.direction = vector_plus(ray.direction, v1);
	ray.direction = vector_plus(ray.direction, v2);
	ray.direction = normalized_vector(ray.direction);
	return (ray);
}

void		set_camera(t_mlx *mlx)
{
	mlx->camera->target = rotate_vector(mlx->camera->origin,
	mlx->camera->target, mlx->camera->rot);
	mlx->camera->rot.x = 0;
	mlx->camera->rot.y = 0;
	perspective_cam(mlx->camera->origin, mlx->camera->target, mlx);
}

void		read_camera(t_mlx *mlx, char *line)
{
	int		arr[10];

	int_array_set(arr, 10, 0);
	int_array_read(arr, 10, line);
	mlx->camera->origin.x = ft_int_clamp_0(arr[0], -99, 99);
	mlx->camera->origin.y = ft_int_clamp_0(arr[1], -99, 99);
	mlx->camera->origin.z = ft_int_clamp_0(arr[2], -99, 99);
	mlx->camera->target.x = ft_int_clamp_0(arr[3], -99, 99);
	mlx->camera->target.y = ft_int_clamp_0(arr[4], -99, 99);
	mlx->camera->target.z = ft_int_clamp_0(arr[5], -99, 99);
	mlx->camera->rot.x = ft_int_clamp_0(arr[6], -180, 180);
	mlx->camera->rot.y = ft_int_clamp_0(arr[7], -180, 180);
	mlx->camera->rot.z = ft_int_clamp_0(arr[8], -180, 180);
	if (mlx->camera->origin.x == mlx->camera->target.x &&
		mlx->camera->origin.y == mlx->camera->target.y &&
		mlx->camera->origin.z == mlx->camera->target.z)
		mlx->camera->target.z = mlx->camera->origin.z - 1;
	if (mlx->camera->origin.x == mlx->camera->target.x &&
		mlx->camera->origin.z == mlx->camera->target.z)
		mlx->camera->target.z = mlx->camera->origin.z - 0.01;
	set_camera(mlx);
}
