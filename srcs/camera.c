/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:18:45 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/05 17:40:00 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_camera	*perspective_cam(t_point origin, t_vector target, t_mlx *mlx)
{
	t_camera	*camera;
	t_vector	up;
	double		aspect_ratio;

	aspect_ratio = mlx->img_width / mlx->img_height;
	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	camera->origin = origin;
	camera->forward = normalized_vector(vector_minus(target, origin));
	up = vector_y();
	camera->right = normalized_vector(cross_vector(camera->forward, up));
	camera->up = cross_vector(camera->right, camera->forward);
	camera->height = tan((FOV * M_PI / 180.0) / 2);
	camera->width = camera->height * aspect_ratio;
	return (camera);
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
