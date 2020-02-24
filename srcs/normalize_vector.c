/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:00:05 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/24 15:51:47 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_vector	normalized_vector(t_vector v)
{
	double		len;
	double		inv_len;
	t_vector	v2;

	len = vector_length(v);
	if (len > 0)
	{
		inv_len = 1 / len;
		v2.x = v.x * inv_len;
		v2.y = v.y * inv_len;
		v2.z = v.z * inv_len;
		return (v2);
	}
	else
		return (v);
}
