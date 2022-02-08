/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:23 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/08 13:59:37 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	distance_to_wall(t_game *g, float ray_angle)
{
	float	d;
	float	x;
	float	y;
	float	ray_cos;
	float	ray_sen;

	ray_cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
	ray_sen = sin(degree_to_radians(ray_angle)) / g->ray.precision;
	x = g->pl.x + .5;
	y = g->pl.y + .5;
	while (g->map[(int)y][(int)x] != '1')
	{
		x += ray_cos;
		y += ray_sen;
		if (g->map[(int)y][(int)x] == '1')
			my_mlx_pixel_put(&g->minimap, x * SIZE, y * SIZE, 0x00FF0000);
		else
			my_mlx_pixel_put(&g->minimap, x * SIZE, y * SIZE, 0x00BDC1C6);
	}
	d = sqrt((x - g->ray.x) * (x - g->ray.x) + (y - g->ray.y) * (y - g->ray.y));
	d = d * cos(degree_to_radians(ray_angle - g->ray.angle));
	return (d);
}

void	cub_draw(t_game *g, int ray_count, float dis)
{
	int	wall_height;
	int	ds;
	int	j;

	wall_height = (int)(g->ray.height / (2 * dis));
	ds = (g->ray.height / 2) - wall_height;
	j = -1;
	while (++j < g->ray.height)
	{
		if (j < ds)
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.ceiling);
		else if (j >= ds && j < ((g->ray.height / 2) + wall_height))
			my_mlx_pixel_put(&g->win_img, ray_count, j, 0x00000000);
		else
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.floor);
	}
}

void	cub_raycast(t_game *g)
{
	float	ray_angle;
	int		ray_count;
	float	dist;

	ray_angle = g->ray.angle - g->ray.hfov;
	ray_count = -1;
	if (g->win_img.img)
		mlx_destroy_image(g->mlx_ptr, g->win_img.img);
	g->win_img.img = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_img.addr = mlx_get_data_addr(g->win_img.img, &g->win_img.bpp, \
		&g->win_img.line_len, &g->win_img.endian);
	while (++ray_count < g->ray.width)
	{
		dist = distance_to_wall(g, ray_angle);
		cub_draw(g, ray_count, dist);
		ray_angle += g->ray.incre_angle;
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.img, 0, 0);
}
