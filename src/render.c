/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:01:06 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/16 18:12:20 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_img	get_texture(t_game *g)
{
	float	small;

	small = 0.004;
	if (g->y - (int)g->y < small)
		return (g->tex.n);
	if ((int)g->y + 1 - g->y < small)
		return (g->tex.s);
	if (g->x - (int)g->x < small)
		return (g->tex.w);
	if ((int)g->x + 1 - g->x < small)
		return (g->tex.e);
	return (g->tex.b);
}

void	redraw_elem(t_game *g, t_img img, int x, int y)
{
	int		p[2];
	t_img	images[2];

	p[0] = x;
	p[1] = y;
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
		cub_miniview(g);
		redraw_elem(g, g->scope, WIN_W / 2 - g->scope.width / 2, \
			WIN_H / 2 - g->scope.height / 2);
		redraw_elem(g, g->miniview, WIN_W - g->miniview.width - 20, \
			WIN_H - g->miniview.height - 20);
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.i, 0, 0);
	}
	g->nframes++;
	return (0);
}
