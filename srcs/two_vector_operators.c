/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_vector_operators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:22:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/05 17:46:56 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_vector	vector_plus(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vector	vector_minus(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vector	vector_multiply(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x * v2.x;
	v3.y = v1.y * v2.y;
	v3.z = v1.z * v2.z;
	return (v3);
}

t_vector	vector_divide(t_vector v1, t_vector v2)
{
	t_vector	v3;

	if (v2.x == 0 || v2.y == 0 || v2.z == 0)
	{
		ft_putendl("Prevented vector division by vector with 0 axis");
		return (v1);
	}
	v3.x = v1.x / v2.x;
	v3.y = v1.y / v2.y;
	v3.z = v1.z / v2.z;
	return (v3);
}
