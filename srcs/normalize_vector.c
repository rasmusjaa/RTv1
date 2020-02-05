/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:00:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/05 17:45:06 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

double		normalize_vector(t_vector *v)
{
	double	len;

	len = vector_length(*v);
	if (len = 0)
	{
		ft_putendl("Prevented vector division by 0 length");
		return (len);
	}
	v->x /= len;
	v->y /= len;
	v->z /= len;
	return (len);
}

t_vector	normalized_vector(t_vector v)
{
	t_vector	v2;

	v2 = copy_vector(v);
	normalize_vector(&v2);
	return (v2);
}
