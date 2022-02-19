/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:11:54 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/19 12:12:31 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	if (!ft_strchr("1c", g->map[(int)(g->pl.y + 0.5 + \
			(3 * ray_sin))][(int)(g->pl.x + 0.5)]))
		g->pl.y += ray_sin;
	if (!ft_strchr("1c", \
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5 + (3 * ray_cos))]))
		g->pl.x += ray_cos;
}

void	action_door(t_game *g)
{
	if (g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5)] == 'c')
		return ;
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_w.i, 0, 0);
	if (g->map[(int)(g->pl.y + 0.5) - 1][(int)(g->pl.x + 0.5)] == 'c')
		g->map[(int)(g->pl.y + 0.5) - 1][(int)(g->pl.x + 0.5)] = 'o';
	else if (g->map[(int)(g->pl.y + 0.5) - 1][(int)(g->pl.x + 0.5)] == 'o')
		g->map[(int)(g->pl.y + 0.5) - 1][(int)(g->pl.x + 0.5)] = 'c';
	if (g->map[(int)(g->pl.y + 0.5) + 1][(int)(g->pl.x + 0.5)] == 'c')
		g->map[(int)(g->pl.y + 0.5) + 1][(int)(g->pl.x + 0.5)] = 'o';
	else if (g->map[(int)(g->pl.y + 0.5) + 1][(int)(g->pl.x + 0.5)] == 'o')
		g->map[(int)(g->pl.y + 0.5) + 1][(int)(g->pl.x + 0.5)] = 'c';
	if (g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) - 1] == 'c')
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) - 1] = 'o';
	else if (g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) - 1] == 'o')
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) - 1] = 'c';
	if (g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) + 1] == 'c')
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) + 1] = 'o';
	else if (g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) + 1] == 'o')
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5) + 1] = 'c';
}
