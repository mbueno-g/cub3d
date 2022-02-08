/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:23 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/08 18:59:09 by aperez-b         ###   ########.fr       */
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
}

float	distance_to_wall(t_game *g, float ray_angle)
{
	float	d;
	float	x;
	float	y;
	float	ray_cos;
	float	ray_sin;

	ray_cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
	ray_sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;
	x = g->pl.x + 0.5;
	y = g->pl.y + 0.5;
	my_mlx_area_put(&g->minimap, \
		ft_newvector((int)x * SIZE, (int)y * SIZE), \
		ft_newvector(SIZE, SIZE), 0x00FDD663);
	while (g->map[(int)y][(int)x] != '1')
	{
		x += ray_cos;
		y += ray_sin;
		if (g->map[(int)y][(int)x] == '1')
			my_mlx_pixel_put(&g->minimap, x * SIZE, y * SIZE, 0x00FF0000);
		else
			my_mlx_pixel_put(&g->minimap, x * SIZE, y * SIZE, 0x00BDC1C6);
	}
	d = sqrt((x - g->pl.x) * (x - g->pl.x) + (y - g->pl.y) * (y - g->pl.y));
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
