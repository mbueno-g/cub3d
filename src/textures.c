/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:25:29 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/17 09:33:51 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_tex_color(t_game *g, t_img *i, int z)
{
	int	color;

	color = 0x00000000;
	if (g->map[(int)g->y][(int)g->x] == '1')
		color = my_mlx_pixel_get(i, (int)(i->width * (g->x + g->y)) \
			% i->width, z);
	else if (g->map[(int)g->y][(int)g->x] == 'o')
		color = 0x0000FF00;
	else if (g->map[(int)g->y][(int)g->x] == 'c')
		color = 0x00FF0000;
	return (color);
}

void	draw_texture(t_game *g, t_img *i, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)i->height;
	ds = ((float)WIN_H / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < i->height)
	{
		color = get_tex_color(g, i, z);
		color = get_dist_color(color, ds);
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)WIN_H)
				my_mlx_pixel_put(&g->win_img, ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

void	cub_draw(t_game *g, int ray_count, float dis)
{
	int		wall_height;
	float	ds;
	int		j;

	wall_height = (int)(WIN_H / (1.5 * dis));
	ds = ((float)WIN_H / 2) - (float)wall_height;
	j = -1;
	while (++j < WIN_H)
	{
		if (j < ds)
			my_mlx_pixel_put(&g->win_img, ray_count, j, \
				get_dist_color(g->tex.ceiling, j));
		else if (j >= (WIN_H / 2) + wall_height)
			my_mlx_pixel_put(&g->win_img, ray_count, j, \
				get_dist_color(g->tex.floor, WIN_H - j));
	}
	draw_texture(g, get_texture(g), ray_count, wall_height);
}
