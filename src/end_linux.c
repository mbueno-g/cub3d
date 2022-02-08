/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_linux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:06:18 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/08 09:40:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_end(t_game *g)
{
	if (g)
	{
		ft_free_matrix(&g->map);
		close(g->fd);
		if (g->tex.n)
			mlx_destroy_image(g->mlx_ptr, g->tex.n);
		if (g->tex.s)
			mlx_destroy_image(g->mlx_ptr, g->tex.s);
		if (g->tex.e)
			mlx_destroy_image(g->mlx_ptr, g->tex.e);
		if (g->tex.w)
			mlx_destroy_image(g->mlx_ptr, g->tex.w);
		if (g->win_img.img)
			mlx_destroy_image(g->mlx_ptr, g->win_img.img);
		if (g->win_ptr)
			mlx_destroy_window(g->mlx_ptr, g->win_ptr);
		if (g->minimap.img)
			mlx_destroy_image(g->mlx_ptr, g->minimap.img);
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
	}
}
