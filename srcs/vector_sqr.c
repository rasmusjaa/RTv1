/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_sqr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:05:40 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/03 14:46:35 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		vector_sqr(t_vector *v)
{
	v->x = double_sqr(v->x);
	v->y = double_sqr(v->y);
	v->z = double_sqr(v->z);
}

t_vector	vector_sqrd(t_vector v)
{
	t_vector	v2;

	v2 = copy_vector(v);
	vector_sqr(&v2);
	return (v2);
}
