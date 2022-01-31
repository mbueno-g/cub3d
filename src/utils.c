/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:10 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/01/31 18:21:12 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	cub_atoi(const char *nptr, short *nbr)
{
	*nbr = 0;
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*nbr = 10 * (*nbr) + (*nptr - '0');
		if (*nbr < 0 || *nbr > 255)
			return (-1);
		nptr++;
	}
	if (*nptr)
		return (-1);
	return (0);
}
