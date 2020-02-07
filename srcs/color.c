/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:28:57 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/06 15:40:43 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

int		color_distance(double dist, int color)
{
	double	intensity;
	double	max;
	int		r;
	int		g;
	int		b;

	max = 10;
	intensity = 1 - (dist / max);
	if (intensity > 1)
		intensity = 1.0;
	intensity = pow(intensity, 2.2);

	r = ((color >> 16) & 0xff) * intensity;
	g = ((color >> 8) & 0xff) * intensity;
	b = (color & 0xff) * intensity;
	color = r<<16 | g<<8 | b;
	return (color);
}
