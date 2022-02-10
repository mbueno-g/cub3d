/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:24:15 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/10 16:41:45 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_minimap(t_game *g)
{
	int	xy[2];
	int	color;

	if (g->minimap.i)
		mlx_destroy_image(g->mlx_ptr, g->minimap.i);
	g->minimap.i = mlx_new_image(g->mlx_ptr, g->width * SIZE, \
		g->height * SIZE);
	g->minimap.addr = mlx_get_data_addr(g->minimap.i, &g->minimap.bpp, \
		&g->minimap.line_len, &g->minimap.endian);
	xy[1] = -1;
	while (++xy[1] < g->height)
	{
		xy[0] = -1;
		while (++xy[0] < g->width)
		{
			if (g->map[xy[1]][xy[0]] != '1')
				color = 0x005E5C64;
			else
				color = 0x008BB5F8;
			my_mlx_area_put(&g->minimap, \
				ft_newvector(xy[0] * SIZE, xy[1] * SIZE), \
				ft_newvector(SIZE, SIZE), color);
		}
	}
}
