/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:09:47 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/03 15:09:50 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

double	vector_length_pwr2(t_vector v)
{
	return (double_sqr(v.x) + double_sqr(v.y) + double_sqr(v.z));
}

double	vector_length(t_vector v)
{
	return (sqrt(vector_length_pwr2(v)));
}
