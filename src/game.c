/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/09 16:01:35 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

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

	angle = g->ray.angle;
	if (k == KEY_A)
		angle = g->ray.angle - 90;
	else if (k == KEY_S)
		angle = g->ray.angle - 180;
	else if (k == KEY_D)
		angle = g->ray.angle + 90;
	ray_cos = cos(degree_to_radians(angle)) * g->pl.speed;
	ray_sin = sin(degree_to_radians(angle)) * g->pl.speed;
	if (g->map[(int)(g->pl.y + ray_sin + 0.5)][(int)(g->pl.x + 0.5)] != '1')
		g->pl.y += ray_sin;
	if (g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + ray_cos + 0.5)] != '1')
		g->pl.x += ray_cos;
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

int	cub_mouse(int x, int y, void *param)
{
	t_game	*g;

	g = param;
	if (x > g->mouse_x && y != -1)
		g->ray.angle += 2;
	else if (y != -1)
		g->ray.angle -= 2;
	g->mouse_x = x;
	return (0);
}

void	game_init(t_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, ":)");
	init_ray(g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win_ptr, 06, 1L << 6, cub_mouse, g);
	mlx_key_hook(g->win_ptr, cub_key, g);
	mlx_loop_hook(g->mlx_ptr, cub_update, g);
	mlx_loop(g->mlx_ptr);
}
