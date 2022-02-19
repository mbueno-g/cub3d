/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/19 14:19:22 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	cub_key(int k, void *param)
{
	if (k == KEY_Q || k == KEY_ESC)
		cub_perror(end, param, NULL, 1);
	if (k == KEY_R)
		((t_game *)param)->neg *= -1;
	if (k == KEY_SPACE)
		action_door(param);
	return (0);
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
		g->ray.angle -= 5;
	if (k == KEY_RIGHT)
		g->ray.angle += 5;
	if (k == KEY_W || k == KEY_A || k == KEY_S || k == KEY_D)
		move_pl(k, g, ray_cos, ray_sin);
	return (0);
}

int	cub_mouse(int x, int y, void *param)
{
	t_game	*g;

	g = param;
	if (x > g->mouse_x && y != -1)
		g->ray.angle += 3;
	else if (x < g->mouse_x && y != -1)
		g->ray.angle -= 3;
	g->mouse_x = x;
	return (0);
}

void	init_attr(t_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, ":)");
	g->win_img.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp, \
		&g->win_img.line_len, &g->win_img.endian);
	g->win_w.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_w.addr = mlx_get_data_addr(g->win_w.i, &g->win_w.bpp, \
		&g->win_w.line_len, &g->win_w.endian);
	my_mlx_area_put(&g->win_w, ft_newvector(0, 0), \
		ft_newvector(WIN_W, WIN_H), 0x00BDC1C6);
	g->minimap.i = mlx_new_image(g->mlx_ptr, g->width * SIZE, \
		g->height * SIZE);
	g->minimap.addr = mlx_get_data_addr(g->minimap.i, &g->minimap.bpp, \
		&g->minimap.line_len, &g->minimap.endian);
	g->miniview.i = mlx_new_image(g->mlx_ptr, 30 * SIZE, 15 * SIZE);
	g->miniview.addr = mlx_get_data_addr(g->miniview.i, &g->miniview.bpp, \
		&g->miniview.line_len, &g->miniview.endian);
	g->miniview.width = 30 * SIZE;
	g->miniview.height = 15 * SIZE;
}

void	game_init(t_game *g)
{
	init_attr(g);
	init_ray(g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win_ptr, 06, 1L << 6, cub_mouse, g);
	mlx_key_hook(g->win_ptr, cub_key, g);
	mlx_loop_hook(g->mlx_ptr, cub_update, g);
	mlx_loop(g->mlx_ptr);
}
