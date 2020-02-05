/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:53:10 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/03 15:08:06 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_vector	copy_vector(t_vector v)
{
	t_vector	v2;

	v2.x = v.x;
	v2.y = v.y;
	v2.z = v.z;
	return (v2);
}

t_vector	negative_vector(t_vector v)
{
	t_vector	v2;

	v2.x = -1 * v.x;
	v2.y = -1 * v.y;
	v2.z = -1 * v.z;
	return (v2);
}

t_vector	set_vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	set_single_vector(double d)
{
	t_vector	v;

	v.x = d;
	v.y = d;
	v.z = d;
	return (v);
}
