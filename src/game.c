/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/08 14:06:11 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_game *g)
{
	g->ray.angle = 0;
	if (g->pl.dir == 'S')
		g->ray.angle = 90;
	else if (g->pl.dir == 'W')
		g->ray.angle = 180;
	if (g->pl.dir == 'N')
		g->ray.angle = 270;
	g->ray.oldangle = g->ray.angle;
	g->ray.hfov = 30;
	g->ray.width = WIN_W;
	g->ray.height = WIN_H;
	g->ray.incre_angle = 2 * g->ray.hfov / g->ray.width;
	g->ray.precision = 20;
	g->ray.lim = 100;
	g->ray.x = g->pl.y;
	g->ray.y = g->pl.x;
}

int	cub_keys(int k, void *param)
{
	t_game	*g;

	g = param;
	if (k == KEY_Q || k == KEY_ESC)
		cub_perror(end, g, NULL, 1);
	if (k == KEY_LEFT)
		g->ray.angle -= 5;
	if (k == KEY_RIGHT)
		g->ray.angle += 5;
	return (0);
}

int	cub_update(void *param)
{
	t_game	*g;

	g = param;
	if (!g->nframes || g->ray.angle != g->ray.oldangle)
	{
		g->ray.oldangle = g->ray.angle;
		cub_minimap(g);
		cub_raycast(g);
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->minimap.img, \
			WIN_W - (g->width * SIZE) - 10, WIN_H - (g->height * SIZE) - 10);
	}
	g->nframes++;
	return (0);
}

void	game_init(t_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, ":)");
	init_ray(g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
	mlx_key_hook(g->win_ptr, cub_keys, g);
	mlx_loop_hook(g->mlx_ptr, cub_update, g);
	mlx_loop(g->mlx_ptr);
}
