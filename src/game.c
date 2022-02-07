/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/07 18:31:10 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_t_data(t_ray *ray, t_game *g)
{
	ray->angle = 270;
	ray->hfov = 30;
	ray->width = 640;
	ray->height = 480;
	ray->incre_angle = 2 * ray->hfov / ray->width;
	ray->precision = 64;
	ray->x = g->pl.y + 3.5;
	ray->y = g->pl.x + 3.5;
}

float	distance_to_wall(t_game *g, t_ray ray, float ray_angle)
{
	float	dist;
	float	x;
	float	y;
	float	ray_cos;
	float	ray_sen;

	ray_cos = cos(degree_to_radians(ray_angle)) / ray.precision;
	ray_sen = sin(degree_to_radians(ray_angle)) / ray.precision;
	x = g->pl.y;
	y = g->pl.x;
	while (g->map[(int)y][(int)x] != '1')
	{
		x += ray_sen;
		y += ray_cos;
	}
	dist = sqrt((x - ray.x) * (x - ray.x) + (y - ray.y) * (y - ray.y));
	return (dist);
}

void	cub_draw(t_game *g, t_ray ray, int ray_count, float dis)
{
	int	wall_height;
	int	ds;
	int	j;

	wall_height = (int)(ray.height / (2 * dis));
	ds = (ray.height / 2) - wall_height;
	j = -1;
	while (++j < ray.height)
	{
		if (j < ds)
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.hex_ceiling);
		else if (j >= ds && j < ((ray.height / 2) + wall_height))
			my_mlx_pixel_put(&g->win_img, ray_count, j, 0x00000000);
		else
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.hex_floor);
	}
}

void	cub_raycast(t_game *g)
{
	t_ray	ray;
	float	ray_angle;
	int		ray_count;
	float	dist;

	init_t_data(&ray, g);
	ray_angle = ray.angle - ray.hfov;
	ray_count = -1;
	g->win_img.img = mlx_new_image(g->mlx_ptr, ray.width, ray.height);
	g->win_img.addr = mlx_get_data_addr(g->win_img.img, &g->win_img.bpp, \
		&g->win_img.line_len, &g->win_img.endian);
	while (++ray_count < ray.width)
	{
		dist = distance_to_wall(g, ray, ray_angle);
		cub_draw(g, ray, ray_count, dist);
		ray_angle += ray.incre_angle;
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.img, 0, 0);
}

void	game_init(t_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, 640, 480, ":)");
	cub_raycast(g);
	//mlx_loop_hook(m->mlx_ptr, ft_reset, &m);
	mlx_hook(g->win_ptr, 17, 0, NULL, &g);
	//mlx_key_hook(m->win_ptr, ft_key_hook, &m);
	mlx_loop(g->mlx_ptr);
}

/*void draw_game(t_map *m)
{
	t_img	i;
	int		j;
	int		z;
	int		w;
	int		h;
	int		color;

	m->win_ptr = mlx_new_window(m->mlx_ptr, 1920, 1080, ":)");
	i.img = mlx_xpm_file_to_image(m->mlx_ptr, "textures/1.xpm", &w, &h);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.line_len, &i.endian);
	j = -1;
	while (++j < h)
	{
		z = -1;
		while (++z < w)
		{
			color = my_mlx_pixel_get(&i, j, z);
			my_mlx_pixel_put(&i, j , z, 2*color);
		}
	}
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, i.img, 0, 0);
	mlx_loop(m->mlx_ptr);
}*/
