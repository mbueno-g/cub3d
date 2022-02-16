/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_linux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:06:18 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/16 17:32:55 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	destroy_images(t_game *g)
{
	if (g->tex.n.i)
		mlx_destroy_image(g->mlx_ptr, g->tex.n.i);
	if (g->tex.s.i)
		mlx_destroy_image(g->mlx_ptr, g->tex.s.i);
	if (g->tex.e.i)
		mlx_destroy_image(g->mlx_ptr, g->tex.e.i);
	if (g->tex.w.i)
		mlx_destroy_image(g->mlx_ptr, g->tex.w.i);
	if (g->tex.b.i)
		mlx_destroy_image(g->mlx_ptr, g->tex.b.i);
	if (g->win_img.i)
		mlx_destroy_image(g->mlx_ptr, g->win_img.i);
	if (g->scope.i)
		mlx_destroy_image(g->mlx_ptr, g->scope.i);
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	if (g->minimap.i)
		mlx_destroy_image(g->mlx_ptr, g->minimap.i);
	if (g->miniview.i)
		mlx_destroy_image(g->mlx_ptr, g->miniview.i);
}

void	cub_end(t_game *g)
{
	if (!g)
		return ;
	ft_free_matrix(&g->map);
	close(g->fd);
	destroy_images(g);
	mlx_destroy_display(g->mlx_ptr);
	free(g->mlx_ptr);
}
