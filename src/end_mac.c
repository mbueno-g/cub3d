/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_mac.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:06:18 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/07 12:51:25 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_end(t_game *g)
{
	if (g)
	{
		ft_free_matrix(&g->map);
		close(g->fd);
		if (g->tex.north)
			mlx_destroy_image(g->mlx_ptr, g->tex.north);
		if (g->tex.south)
			mlx_destroy_image(g->mlx_ptr, g->tex.south);
		if (g->tex.east)
			mlx_destroy_image(g->mlx_ptr, g->tex.east);
		if (g->tex.west)
			mlx_destroy_image(g->mlx_ptr, g->tex.west);
		if (g->win_img.img)
			mlx_destroy_image(g->mlx_ptr, g->win_img.img);
	}
}
