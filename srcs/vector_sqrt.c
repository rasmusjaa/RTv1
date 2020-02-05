/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_sqrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:05:40 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/03 14:58:26 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		vector_sqrt(t_vector *v)
{
	v->x = sqrt(v->x);
	v->y = sqrt(v->y);
	v->z = sqrt(v->z);
}

t_vector	vector_sqrtd(t_vector v)
{
	t_vector	v2;

	v2 = copy_vector(v);
	vector_sqrt(&v2);
	return (v2);
}
