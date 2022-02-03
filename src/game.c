/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:15 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/03 19:04:07 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void game_init(t_map *m)
{
	m->win_ptr = mlx_new_window(m->mlx_ptr, 1920, 1080, ":)");
	//mlx_loop_hook(m->mlx_ptr, ft_reset, &m);
	mlx_hook(m->win_ptr, 17, 0, NULL, &m);
	//mlx_key_hook(m->win_ptr, ft_key_hook, &m);
	mlx_loop(m->mlx_ptr);
}

void draw_game(t_map *m)
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
}
