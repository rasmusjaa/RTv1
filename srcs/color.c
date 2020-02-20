/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:28:57 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/20 15:00:20 by rjaakonm         ###   ########.fr       */
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
	d = dot_vector(light, x->hitnormal);
	intensity = mlx->spots[spot].intensity / distance;
	if (intensity > 1)
		intensity = 1.0;
	intensity = pow(intensity, GAMMA);
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

	camera = vector_minus(mlx->camera->origin, x->hitpoint);
	camera = normalized_vector(camera);
	d = dot_vector(x->hitnormal, camera);

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
	while (spot < mlx->spot_i)
	{
		d += spot_shading(mlx, x, spot);
		spot++;
	}
	if (d > 1)
		d = 1;
	spot = 0;
	specular = 0;
	while (spot < mlx->spot_i)
	{
		shadow = check_shadow(mlx, x, spot);
		if (shadow == 1)
		{
			d *= 0.5;
		}
		else
		{
			specular = ft_dpow(spot_specular(mlx, x, spot), 32) * 255;
		}
		spot++;
	}
	if (d > 1)
		d = 1;

	// kato noise varjoista

	rgb[0] = ((x->color >> 16) & 0xff) * d + (int)specular;
	rgb[1] = ((x->color >> 8) & 0xff) * d + (int)specular;
	rgb[2] = (x->color & 0xff) * d + (int)specular;

	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;

	if (mlx->mouse_3 == 1)
	{
		ft_printf("r %d\n",	rgb[0]);
	}

	x->color = rgb[0]<<16 | rgb[1]<<8 | rgb[2];

}
