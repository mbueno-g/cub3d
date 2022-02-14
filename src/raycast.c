/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:23 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/14 19:04:54 by mbueno-g         ###   ########.fr       */
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
	else if (g->pl.dir == 'N')
		g->ray.angle = 270;
	g->ray.oldangle = g->ray.angle;
	g->ray.hfov = 30;
	g->ray.incre_angle = 2 * g->ray.hfov / WIN_W;
	g->ray.precision = 100;
}

float	distance_to_wall(t_game *g, float ray_angle)
{
	float	d;
	float	ray_cos;
	float	ray_sin;

	ray_cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
	ray_sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;
	g->x = g->pl.x + 0.5;
	g->y = g->pl.y + 0.5;
	while (g->map[(int)g->y][(int)g->x] != '1')
	{
		g->x += ray_cos;
		g->y += ray_sin;
		if (g->map[(int)g->y][(int)g->x] == '1')
			my_mlx_pixel_put(&g->minimap, g->x * SIZE, g->y * SIZE, 0x00FF0000);
		else
			my_mlx_pixel_put(&g->minimap, g->x * SIZE, g->y * SIZE, 0x00BDC1C6);
	}
	my_mlx_area_put(&g->minimap, ft_newvector((int)(g->pl.x + 0.5) * SIZE, \
		(int)(g->pl.y + 0.5) * SIZE), ft_newvector(SIZE, SIZE), 0x00FDD663);
	d = sqrt(powf(g->x - g->pl.x - 0.5, 2.) + powf(g->y - g->pl.y - 0.5, 2.));
	d = d * cos(degree_to_radians(ray_angle - g->ray.angle));
	return (d);
}

void	draw_texture(t_game *g, t_img i, int ray_count, int wall_height, float ds)
{
	float	dy;
	float	y;
	int	z;
	int	color;
	float c;

	dy = ((float) wall_height * 2)/ (float) i.height;
	y = ds;
	z = -1;
	while (++z < i.height)
	{
		color = my_mlx_pixel_get(&i, (int)(i.width * (g->x + g->y)) \
			% i.width, z);
		c = y;
		while (c < y + dy)
		{
			my_mlx_pixel_put(&g->win_img, ray_count, c, color);
			c++;
		}
		y += dy;
	}
}

void	cub_draw(t_game *g, int ray_count, float dis)
{
	int	wall_height;
	float ds;
	int	j;
	int	pos;
	int i;

	wall_height = (int)(WIN_H / (2 * dis));
	ds = (float) (WIN_H / 2) -  (float) wall_height;
	j = -1;
	i = 0;
	pos = g->tex.n.height / ((WIN_H / 2) + wall_height - ds);
	while (++j < WIN_H)
	{
		if (j < ds)
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.ceiling);
		else if (j >= (WIN_H / 2) + wall_height)
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.floor);
	}
	printf("%f\n", (float) ds);
	if (ds > 0)
		draw_texture(g, g->tex.n, ray_count, wall_height, ds);
}

void	cub_raycast(t_game *g)
{
	float	ray_angle;
	int		ray_count;
	float	dist;

	if (g->win_img.i)
		mlx_destroy_image(g->mlx_ptr, g->win_img.i);
	g->win_img.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp, \
		&g->win_img.line_len, &g->win_img.endian);
	ray_angle = g->ray.angle - g->ray.hfov;
	ray_count = -1;
	while (++ray_count < WIN_W)
	{
		dist = distance_to_wall(g, ray_angle);
		cub_draw(g, ray_count, dist);
		ray_angle += g->ray.incre_angle;
	}
}
