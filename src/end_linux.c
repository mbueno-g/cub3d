/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_linux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:06:18 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/09 15:32:48 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_end(t_game *g)
{
	if (g)
	{
		ft_free_matrix(&g->map);
		close(g->fd);
		if (g->tex.n.i)
			mlx_destroy_image(g->mlx_ptr, g->tex.n.i);
		if (g->tex.s.i)
			mlx_destroy_image(g->mlx_ptr, g->tex.s.i);
		if (g->tex.e.i)
			mlx_destroy_image(g->mlx_ptr, g->tex.e.i);
		if (g->tex.w.i)
			mlx_destroy_image(g->mlx_ptr, g->tex.w.i);
		if (g->win_img.i)
			mlx_destroy_image(g->mlx_ptr, g->win_img.i);
		if (g->scope.i)
			mlx_destroy_image(g->mlx_ptr, g->scope.i);
		if (g->win_ptr)
			mlx_destroy_window(g->mlx_ptr, g->win_ptr);
		if (g->minimap.i)
			mlx_destroy_image(g->mlx_ptr, g->minimap.i);
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
	}
}
