/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:10 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/17 12:48:34 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

t_img	*mlx_load_img(void *ptr, char *path)
{
	int		fd;
	t_img	*i;

	i = malloc(sizeof(t_img));
	i->i = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (i);
	close(fd);
	i->i = mlx_xpm_file_to_image(ptr, path, &i->width, &i->height);
	i->addr = mlx_get_data_addr(i->i, &i->bpp, &i->line_len, &i->endian);
	return (i);
}

int	cub_atoi(const char *nptr, short *nbr)
{
	*nbr = 0;
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*nbr = 10 * (*nbr) + (*nptr - '0');
		if (*nbr < 0 || *nbr > 255)
			return (-1);
		nptr++;
	}
	if (*nptr)
		return (-1);
	return (0);
}

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

int	checkcn(char *m, char c, int n0, int n1)
{
	int	i;

	i = n0;
	while (i >= 0 && i < n1 && i < (int) ft_strlen(m))
	{
		if (m[i] != c)
			return (1);
		i++;
	}
	return (0);
}
