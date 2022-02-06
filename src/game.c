/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/06 21:19:43 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_t_data(t_data *d, t_map *m)
{
	d->angle = 90;
	d->hfov = 30;
	d->width = 640;
	d->height = 480;
	d->incre_angle = 60 / 640;
	d->precision = 64;
	d->x = m->pl.v.y;
	d->y = m->pl.v.x;
}

float	distance_to_wall(t_map *m, t_data d, float ray_angle)
{
	float	dis;
	float	x;
	float	y;
	float	ray_cos;
	float	ray_sen;

	ray_cos = cos(degree_to_radians(ray_angle)) / d.precision;
	ray_sen = sin(degree_to_radians(ray_angle)) / d.precision;
	x = m->pl.v.y;
	y = m->pl.v.x;
	while (m->map[(int) y][(int) x] != '1')
	{
		x += ray_sen;
		y += ray_cos;
	}
	dis = sqrt((x - d.x) * (x - d.x) + (y - d.y) * (y - d.y));
	return (dis);
}

void	draw(t_map *m, t_data d, int ray_count, float dis)
{
	int	wall_height;
	int	ds;
	int	j;

	wall_height = (int)(d.height / (2 * dis));
	ds = 240 - wall_height;
	j = -1;
	while (++j < 480)
	{
		if (j < ds)
			my_mlx_pixel_put(&d.i, ray_count, j, m->tex.hex_ceiling);
		else if (j >= ds && j < (240 + wall_height))
			my_mlx_pixel_put(&d.i, ray_count, j, 0x000000);
		else
			my_mlx_pixel_put(&d.i, ray_count, j, m->tex.hex_floor);
	}
}

void	raicasting(t_map *m)
{
	t_data	d;
	float	ray_angle;
	int		ray_count;
	float	dis;

	init_t_data(&d, m);
	ray_angle = d.angle - d.hfov;
	ray_count = -1;
	d.i.img = mlx_new_image(m->mlx_ptr, d.width, d.height);
	d.i.addr = mlx_get_data_addr(d.i.img, &d.i.bpp, &d.i.line_len, &d.i.endian);
	while (++ray_count < d.width)
	{
		dis = distance_to_wall(m, d, ray_angle);
		draw(m, d, ray_count, dis);
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, d.i.img, 0, 0);
		ray_angle += 0.09375;
	}
}

void	game_init(t_map *m)
{
	m->win_ptr = mlx_new_window(m->mlx_ptr, 640, 480, ":)");
	raicasting(m);
	//mlx_loop_hook(m->mlx_ptr, ft_reset, &m);
	mlx_hook(m->win_ptr, 17, 0, NULL, &m);
	//mlx_key_hook(m->win_ptr, ft_key_hook, &m);
	mlx_loop(m->mlx_ptr);
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
