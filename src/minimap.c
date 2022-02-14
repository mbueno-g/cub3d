/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:24:15 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/14 14:51:31 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_miniview(t_game *g)
{
	int	xy[2];
	int	aux[2];

	aux[1] = -1;
	xy[1] = (g->pl.y + 0.5 - 10) * SIZE;
	while (++aux[1] < (20 * SIZE))
	{
		aux[0] = -1;
		xy[0] = (g->pl.x + 0.5 - 10) * SIZE;
		while (++aux[0] < (20 * SIZE))
		{
			if (xy[1] >= 0 && xy[1] < (g->height * SIZE) && xy[0] >= 0 \
						&& xy[0] < (g->width * SIZE))
				my_mlx_pixel_put(&g->miniview, aux[0], aux[1], \
					my_mlx_pixel_get(&g->minimap, xy[0], xy[1]));
			else
				my_mlx_pixel_put(&g->miniview, aux[0], aux[1], 0x00000000);
			xy[0]++;
		}
		xy[1]++;
	}
}

void	cub_minimap(t_game *g)
{
	int	xy[2];
	int	color;
	int	len;

	xy[1] = -1;
	while (++xy[1] < g->height)
	{
		xy[0] = -1;
		len = ft_strlen(g->map[xy[1]]);
		while (++xy[0] < len)
		{
			if (ft_isspace(g->map[xy[1]][xy[0]]))
				color = 0x00000000;
			else if (g->map[xy[1]][xy[0]] != '1')
				color = 0x005E5C64;
			else
				color = 0x008BB5F8;
			my_mlx_area_put(&g->minimap, \
				ft_newvector(xy[0] * SIZE, xy[1] * SIZE), \
				ft_newvector(SIZE, SIZE), color);
		}
	}
}
