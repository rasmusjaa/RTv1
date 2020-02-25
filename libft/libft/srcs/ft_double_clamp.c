/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_clamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:06:09 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 16:11:52 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_double_clamp_0(double nb, double min, double max)
{
	if (nb < min)
		return (0);
	if (nb > max)
		return (0);
	return (nb);
}

double	ft_double_clamp(double nb, double min, double max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}
