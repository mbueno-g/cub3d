/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:43:33 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/19 13:46:19 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(t_color c)
{
	return (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
}

t_color	create_rgbt(int col)
{
	t_color	c;

	c.t = (col >> 24) & 0xFF;
	c.r = (col >> 16) & 0xFF;
	c.g = (col >> 8) & 0xFF;
	c.b = col & 0xFF;
	return (c);
}

void	get_cf_color(char **dir, t_game *g)
{
	char	**fc;
	int		str[2];
	int		c[3];
	t_color	aux;

	aux.t = 0;
	str[0] = !ft_strncmp(dir[0], "F", 2);
	str[1] = !ft_strncmp(dir[0], "C", 2);
	fc = ft_split(dir[1], ',');
	if (!fc || ft_matrixlen(fc) != 3)
	{
		ft_free_matrix(&fc);
		return ;
	}
	c[0] = cub_atoi(fc[0], &aux.r);
	c[1] = cub_atoi(fc[1], &aux.g);
	c[2] = cub_atoi(fc[2], &aux.b);
	ft_free_matrix(&fc);
	if (c[0] || c[1] || c[2])
		return ;
	if (str[0])
		g->tex.floor = create_trgb(aux);
	else if (str[1])
		g->tex.ceiling = create_trgb(aux);
}

void	cub_invert_color(t_game *g)
{
	int		xy[2];

	xy[1] = -1;
	while (++xy[1] < WIN_H)
	{
		xy[0] = -1;
		while (++xy[0] < WIN_W)
		{
			my_mlx_pixel_put(&g->win_img, xy[0], xy[1], 0xFFFFFF - \
				my_mlx_pixel_get(&g->win_img, xy[0], xy[1]));
		}
	}
}

int	get_dist_color(int color, float ds, int tr)
{
	t_color	c;
	float	dif;

	if (ds < 0)
		ds = 0;
	dif = powf(1.14, ds / 7.5);
	c = create_rgbt(color);
	if (tr)
		c.t -= dif;
	else
		c.t = 256;
	c.r -= dif;
	c.g -= dif;
	c.b -= dif;
	if (c. t < 0)
		c.t = 0;
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	return (create_trgb(c));
}
