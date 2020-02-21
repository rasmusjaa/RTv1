/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:28:57 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/21 17:26:49 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int	check_shadow(t_mlx *mlx, t_intersection *x, int spot)
{
	t_ray			ray;
	t_intersection	ix;
	int				i;

	ray.start = x->hitpoint;
	ray.direction = vector_minus(mlx->spots[spot].p, x->hitpoint);
	ray.direction = normalized_vector(ray.direction);
	ix = get_intersection(ray, mlx);
	i = 0;
	while (i < 10)
	{
		if (i < mlx->sphere_i)
			sphere_intersection(mlx->spheres[i], &ix);
		if (i < mlx->plane_i)
			plane_intersection(mlx->planes[i], &ix);
		i++;
	}

	double		len;
	t_vector	light;

	light = vector_minus(mlx->spots[spot].p, x->hitpoint);
	len = vector_length(light);

	if (mlx->mouse_3 == 1)
	{
		ft_printf("spot %d: closest %f light dist %f\n", spot, ix.closest, len);
	}
	if (len <= ix.closest)// || (ix.closest <= RAY_T_MIN))
	{
		if (mlx->mouse_3 == 1)
		{
			ft_printf("not in shadow\n");
		}
		return (0);
	}
	if (mlx->mouse_3 == 1)
	{
		ft_printf("is in shadow\n");
	}
	return(1);
}

static double	spot_shading(t_mlx *mlx, t_intersection *x, int spot)
{
	double		d;
	double		distance;
	double		intensity;
	t_vector	light;

	light = vector_minus(mlx->spots[spot].p, x->hitpoint);
	distance = vector_length(light);
	light = normalized_vector(light);
	if (mlx->scene->shading == 1)
		d = dot_vector(light, x->hitnormal);
	else
		d = 1;
	if (mlx->spots[spot].type == 1)
		intensity = mlx->spots[spot].intensity / 100;
	else
		intensity = mlx->spots[spot].intensity * (1 / (1 + distance + pow(distance, 2)));
	if (mlx->mouse_3 == 1)
	{
		ft_printf("spot %d: power %f distance %f intensity %f ",
		spot, mlx->spots[spot].intensity, distance, intensity);
		ft_printf("distance %f shading multiplier %f\n",
		d);
	}
	d *= intensity;
	if (d < 0)
		d = 0;
	return (d);
}

static double	spot_specular(t_mlx *mlx, t_intersection *x, int spot)
{
	double		d;
	t_vector	camera;
	t_vector	light;

	double		intensity;

	light = vector_minus(x->hitpoint, mlx->spots[spot].p);
	intensity = mlx->spots[spot].intensity / vector_length(light);
	if (intensity > 1)
		intensity = 1.0;
	if (mlx->mouse_3 == 1)
	{
		ft_printf("spot %d: len %f intense %f\n", spot, vector_length(light), intensity);
	}

	camera = vector_minus(x->hitpoint, mlx->camera->origin);
	camera = normalized_vector(camera);
	t_vector reflection;

	reflection = vector_multiply_nb(x->hitnormal, 2 * dot_vector(x->hitnormal, light));
	reflection = vector_minus(reflection, light);
	reflection = normalized_vector(reflection);
	d = dot_vector(reflection, camera); // camera to light for cool effect
	if (d < 0)
		d = 0;
	if (mlx->mouse_3 == 1)
	{
		ft_printf("spot %d: specular %f\n",	spot, d);
	}
	return (d);
}

void		ray_color(t_mlx *mlx, t_intersection *x)
{
	int		spot;
	double	d;
	double	specular;
	int		shadow;
	int		rgb[3];

	d = 0;
	spot = 0;
	specular = 0;
	while (spot < mlx->spot_i)
	{
		shadow = check_shadow(mlx, x, spot);
		if (shadow != 1 || mlx->scene->shadows == 0)
		{
			d += spot_shading(mlx, x, spot);
			if (mlx->scene->speculars == 1)
				specular += ft_dpow(spot_specular(mlx, x, spot), 32) * 255;
		}
		spot++;
	}
	d += (double)mlx->scene->ambient / 100;
	if (d > 1)
		d = 1;

	rgb[0] = ((x->color >> 16) & 0xff) * d + (int)specular + mlx->scene->ambient_r;
	rgb[1] = ((x->color >> 8) & 0xff) * d + (int)specular + mlx->scene->ambient_g;
	rgb[2] = (x->color & 0xff) * d + (int)specular + mlx->scene->ambient_b;

	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	x->color = rgb[0]<<16 | rgb[1]<<8 | rgb[2];

}
