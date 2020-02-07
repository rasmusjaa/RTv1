/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:18:45 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/06 16:23:35 by rjaakonm         ###   ########.fr       */
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
	camera->up = cross_vector(camera->right, camera->forward);
	camera->height = tan((FOV * M_PI / 180.0) / 2);
	camera->width = camera->height * ASPECT_RATIO;
}

t_ray		camera_ray(t_camera *camera, t_point target)
{
	t_ray	ray;

	ray.start = camera->origin;
	ray.direction = copy_vector(camera->forward);
	ray.direction.x += target.x * camera->width * camera->right.x;
	ray.direction.y = target.y * camera->height * camera->up.y;
	ray.direction = normalized_vector(ray.direction);
	return (ray);
}
