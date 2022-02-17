/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <mbueno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:19:25 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/17 19:41:51 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_walls(t_game *g, int i, int j)
{
	if (j - 1 >= 0 && j - 1 < g->height)
	{
		if (i - 1 >= 0 && i - 1 < (int)ft_strlen(g->map[j - 1]))
			cub_perror(inv_wall, g, NULL, g->map[j - 1][i - 1] == '0');
		if (i + 1 >= 0 && i + 1 < (int)ft_strlen(g->map[j - 1]))
			cub_perror(inv_wall, g, NULL, g->map[j - 1][i + 1] == '0');
		if (i >= 0 && i < (int)ft_strlen(g->map[j - 1]))
			cub_perror(inv_wall, g, NULL, g->map[j - 1][i] == '0');
	}
	if (i - 1 >= 0 && i - 1 < (int)ft_strlen(g->map[j]))
		cub_perror(inv_wall, g, NULL, g->map[j][i - 1] == '0');
	if (i + 1 >= 0 && i + 1 < (int)ft_strlen(g->map[j]))
		cub_perror(inv_wall, g, NULL, g->map[j][i + 1] == '0');
	if (j + 1 >= 0 && j + 1 < g->height)
	{
		if (i - 1 >= 0 && i - 1 < (int)ft_strlen(g->map[j + 1]))
			cub_perror(inv_wall, g, NULL, g->map[j + 1][i - 1] == '0');
		if (i + 1 >= 0 && i + 1 < (int)ft_strlen(g->map[j + 1]))
			cub_perror(inv_wall, g, NULL, g->map[j + 1][i + 1] == '0');
		if (i >= 0 && i < (int)ft_strlen(g->map[j + 1]))
			cub_perror(inv_wall, g, NULL, g->map[j + 1][i] == '0');
	}
}

void	check_characters(t_game *g, int i, int j)
{
	if (!g->pl.dir && ft_strchr("NSWE", g->map[j][i]))
	{
		g->pl.dir = g->map[j][i];
		g->pl.x = (float)i;
		g->pl.y = (float)j;
	}
	else if (g->pl.dir && ft_strchr("NSWE", g->map[j][i]))
		cub_perror(inv_player, g, NULL, 1);
	else if (!ft_strchr("01oc", g->map[j][i]))
		cub_perror(inv_charac, g, NULL, 1);
	if (j == g->height - 1 && !g->pl.dir)
		cub_perror(inv_player, g, NULL, 1);
}

void	check_elements(t_game *g, int j)
{
	int	i;
	int	k1;
	int	k2;

	i = -1;
	while (++i < (int) ft_strlen(g->map[j]))
	{
		if (g->map[j][i] == ' ')
			check_walls(g, i, j);
		else
			check_characters(g, i, j);
	}
	if (j + 1 < g->height)
	{
		k1 = ft_strlen(g->map[j]) - 1;
		k2 = ft_strlen(g->map[j + 1]) - 1;
		while (g->map[j][k1] == ' ')
			k1--;
		while (g->map[j + 1][k2] == ' ')
			k2--;
		if (k1 - k2 < 0)
			cub_perror(inv_wall, g, NULL, checkcn(g->map[j + 1], '1', k1, k2));
		else if (k1 - k2 > 0)
			cub_perror(inv_wall, g, NULL, checkcn(g->map[j], '1', k2, k1));
	}
}
