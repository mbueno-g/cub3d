/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:01:06 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/10 09:49:01 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	redraw_elem(t_game *g, t_img img, int x, int y)
{
	int		p[2];
	t_img	images[2];

	p[0] = x - (img.width / 2);
	p[1] = y - (img.height / 2);
	images[0] = img;
	images[1] = g->win_img;
	mlx_img_to_img(p, images, 0xFF000000);
}

int	cub_update(void *param)
{
	t_game	*g;

	g = param;
	if (!g->nframes || g->ray.angle != g->ray.oldangle || \
		g->pl.oldx != g->pl.x || g->pl.oldy != g->pl.y)
	{
		g->ray.oldangle = g->ray.angle;
		g->pl.oldx = g->pl.x;
		g->pl.oldy = g->pl.y;
		cub_minimap(g);
		cub_raycast(g);
		redraw_elem(g, g->scope, WIN_W / 2, WIN_H / 2);
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, \
			g->win_img.i, 0, 0);
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->minimap.i, \
			WIN_W - (g->width * SIZE) - 10, WIN_H - (g->height * SIZE) - 10);
	}
	g->nframes++;
	return (0);
}
