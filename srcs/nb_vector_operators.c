/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_vector_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:27:27 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/05 17:44:08 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

t_vector	vector_multiply_nb(t_vector v1, double nb)
{
	t_vector	v2;

	v2.x = v1.x * nb;
	v2.y = v1.y * nb;
	v2.z = v1.z * nb;
	return (v2);
}

t_vector	vector_divide_nb(t_vector v1, double nb)
{
	t_vector	v2;

	if (nb = 0)
	{
		ft_putendl("Prevented vector division by 0");
		return (v1);
	}
	v2.x = v1.x / nb;
	v2.y = v1.y / nb;
	v2.z = v1.z / nb;
	return (v2);
}
