/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:43:33 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/01/31 18:55:05 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(t_color c)
{
	return (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
}

void	get_cf_color(char **dir, t_map *m)
{
	char	**fc;
	int 	f;
	int		c;
	t_color aux;

	aux.t = 255;
	f = !ft_strncmp(dir[0], "F", 2);
	fc = ft_split(dir[1], ',');
	c = cub_atoi(fc[0], &aux.r) || cub_atoi(fc[1], &aux.g) || \
		cub_atoi(fc[2], &aux.b);
	ft_free_matrix(&fc);
	if (c)
		cub_perror(inv_color, m->map, dir[1]);
	if (f)
		m->hex_floor = create_trgb(aux);
	else
		m->hex_ceiling = create_trgb(aux);
}
