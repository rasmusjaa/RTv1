/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:28:57 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 18:36:46 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

static int		check_shadow(t_mlx *mlx, t_intersection *x, int spot)
{
	t_ray			ray;
	t_intersection	ix;
	int				i;
	double			len;
	t_vector		light;

	ray.start = x->hitpoint;
	ray.direction = vector_minus(mlx->spots[spot].p, x->hitpoint);
	ray.direction = normalized_vector(ray.direction);
	ix = get_intersection(ray, mlx);
	i = 0;
	while (i < 10)
	{
		if (i < mlx->sphere_i)
			sphere_intersection(mlx->spheres[i], &ix, i);
		if (i < mlx->plane_i)
			plane_intersection(mlx->planes[i], &ix, i);
		if (i < mlx->cylinder_i)
			cylinder_intersection(mlx->cylinders[i], &ix, i);
		if (i < mlx->cone_i)
			cone_intersection(mlx->cones[i], &ix, i);
		i++;
	}
	set_hit(mlx, &ix);
	light = vector_minus(mlx->spots[spot].p, x->hitpoint);
	len = vector_length(light);
	if (len <= ix.closest || (ix.closest <= RAY_T_MIN))
		return (0);
	return (1);
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
		intensity = mlx->spots[spot].intensity *
		(1 / (1 + distance + pow(distance, 2)));
	d *= intensity;
	d = ft_double_clamp(d, 0, 1);
	return (d);
}

static double	spot_specular(t_mlx *mlx, t_intersection *x, int spot)
{
	double		d;
	t_vector	camera;
	t_vector	light;
	double		intensity;
	t_vector	reflection;

	light = vector_minus(x->hitpoint, mlx->spots[spot].p);
	intensity = mlx->spots[spot].intensity / vector_length(light);
	if (intensity > 1)
		intensity = 1.0;
	camera = vector_minus(x->hitpoint, mlx->camera->origin);
	camera = normalized_vector(camera);
	reflection = vector_multiply_nb(x->hitnormal, 2 *
		dot_vector(x->hitnormal, light));
	reflection = vector_minus(reflection, light);
	reflection = normalized_vector(reflection);
	d = dot_vector(reflection, camera);
	d = ft_double_clamp(d, 0, 1);
	return (d * intensity);
}

static void		add_colors(t_mlx *mlx, t_intersection *x,
	double d, double specular)
{
	int		rgb[3];

	rgb[0] = ((x->color >> 16) & 0xff) * d + specular + mlx->scene->ambient_r;
	rgb[1] = ((x->color >> 8) & 0xff) * d + specular + mlx->scene->ambient_g;
	rgb[2] = (x->color & 0xff) * d + specular + mlx->scene->ambient_b;
	rgb[0] = ft_int_clamp(rgb[0], 0, 255);
	rgb[1] = ft_int_clamp(rgb[1], 0, 255);
	rgb[2] = ft_int_clamp(rgb[2], 0, 255);
	x->color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
}

void			ray_color(t_mlx *mlx, t_intersection *x)
{
	int		spot;
	double	d;
	double	specular;
	int		shadow;

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
	d = ft_double_clamp(d, 0, 1);
	add_colors(mlx, x, d, specular);
}
