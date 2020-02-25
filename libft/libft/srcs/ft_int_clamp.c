/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_clamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:06:09 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 16:11:33 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_int_clamp_0(int nb, int min, int max)
{
	if (nb < min)
		return (0);
	if (nb > max)
		return (0);
	return (nb);
}

int		ft_int_clamp(int nb, int min, int max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}
