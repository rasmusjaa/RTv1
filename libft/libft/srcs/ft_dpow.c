/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:14:48 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/21 15:21:37 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double			ft_dpow(double n, int pow)
{
	int			i;
	double		total;

	i = 1;
	total = n;
	while (i < pow)
	{
		total = total * n;
		i++;
	}
	return (total);
}
