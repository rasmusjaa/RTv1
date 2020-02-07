/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:18:45 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/07 16:11:44 by rjaakonm         ###   ########.fr       */
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
	camera->up = normalized_vector(cross_vector(camera->right, camera->forward));
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
