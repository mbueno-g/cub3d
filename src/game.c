/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/08 19:01:45 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	cub_key(int k, void *param)
{
	t_game	*g;

	g = param;
	if (k == KEY_Q || k == KEY_ESC)
		cub_perror(end, g, NULL, 1);
	return (0);
}

void	move_pl(int k, t_game *g, float ray_cos, float ray_sin)
{
	float	angle;

	if (k == KEY_A)
		angle = g->ray.angle - 90;
	else if (k == KEY_S)
		angle = g->ray.angle - 180;
	else if (k == KEY_D)
		angle = g->ray.angle + 90;
	else
		angle = g->ray.angle;
	ray_cos = cos(degree_to_radians(angle)) / g->ray.precision;
	ray_sin = sin(degree_to_radians(angle)) / g->ray.precision;
	g->pl.x += (2 * ray_cos);
	g->pl.y += (2 * ray_sin);
}

int	cub_keydown(int k, void *param)
{
	t_game	*g;
	float	ray_cos;
	float	ray_sin;

	ray_cos = 0;
	ray_sin = 0;
	g = param;
	if (k == KEY_LEFT)
		g->ray.angle -= 4;
	if (k == KEY_RIGHT)
		g->ray.angle += 4;
	if (k == KEY_W || k == KEY_A || k == KEY_S || k == KEY_D)
		move_pl(k, g, ray_cos, ray_sin);
	return (0);
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
	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_key_hook(g->win_ptr, cub_key, g);
	mlx_loop_hook(g->mlx_ptr, cub_update, g);
	mlx_loop(g->mlx_ptr);
}
