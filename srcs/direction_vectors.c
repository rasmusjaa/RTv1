/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_vectors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:50:48 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/03 20:07:27 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_vector	vector_x(void)
{
	t_vector	v;

	v.x = 1;
	v.y = 0;
	v.z = 0;
	return (v);
}

t_vector	vector_y(void)
{
	t_vector	v;

	v.x = 0;
	v.y = 1;
	v.z = 0;
	return (v);
}

t_vector	vector_z(void)
{
	t_vector	v;

	v.x = 0;
	v.y = 0;
	v.z = 1;
	return (v);
}

t_vector	vector_0(void)
{
	t_vector	v;

	v.x = 0;
	v.y = 0;
	v.z = 0;
	return (v);
}
