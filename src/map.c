/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <mbueno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:05:52 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/03 16:19:17 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdio.h>

void	check_textures(char *trim, t_map *m)
{
	char	**dir;
	int		w;

	dir = ft_split(trim, ' ');
	ft_putmatrix_fd(dir, 1, 1);
	if (!dir)
	{
		free(trim);
		cub_perror(no_memory, m, NULL, 1);
	}
	else if (!ft_strncmp(dir[0], "NO", 3))
		m->tex.north = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "SO", 3))
		m->tex.south = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "WE", 3))
		m->tex.west = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "EA", 3))
		m->tex.east = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "F", 2) || !ft_strncmp(dir[0], "C", 2))
		get_cf_color(dir, m);
	ft_free_matrix(&dir);
}

void	read_map(char *file, t_map *m)
{
	char	*line;
	char	*aux;
	int		i;

	i = 0;
	m->fd = open(file, O_RDONLY);
	cub_perror(inv_file, m, file, m->fd < 0);
	while (1)
	{
		line = get_next_line(m->fd);
		if (!line)
			break ;
		aux = ft_strtrim(line, "\n");
		free(line);
		if (aux && aux[0] && ++i < 7)
			check_textures(aux, m);
		else if ((aux && aux[0]) || i >= 7)
			m->map = ft_extend_matrix(m->map, aux);
		free(aux);
	}
	cub_perror(empty_file, m, NULL, !i);
	m->height = ft_matrixlen(m->map);
	if (!m->tex.north || !m->tex.south || !m->tex.east || !m->tex.west)
		cub_perror(inv_tex, m, NULL, 1);
}

void	check_characters(int j, t_map *m)
{
	int	i;

	i = -1;
	while (++i < (int) ft_strlen(m->map[j]))
	{
		if (ft_strchr("NSWE", m->map[j][i]) && m->dir == 'M')
			m->dir = m->map[j][i];
		else if (!ft_strchr("01", m->map[j][i]))
			cub_perror(inv_charac, m, NULL, 1);
	}
	if (j == m->height - 1 && m->dir == 'M')
		cub_perror(no_player, m, NULL, 1);
}

void	check_map(char *file, t_map *m)
{
	int	j;
	int	i;
	int	w;

	read_map(file, m);
	j = 0;
	while (j < m->height)
	{
		w = ft_strlen(m->map[j]);
		i = 0;
		if (ft_strncmp(m->map[j], "", 1) == 0)
			cub_perror(inv_map, m, NULL, 1);
		while (ft_isspace(m->map[j][i]) && i < w)
			i++;
		if ((j == 0 || j == m->height - 1) && w - i - \
			ft_countchar(m->map[j], '1'))
			cub_perror(inv_wall, m, NULL, 1);
		else if (m->map[j][i] != '1' || m->map[j][w - 1] != '1')
			cub_perror(inv_wall, m, NULL, 1);
		check_characters(j, m);
		j++;
	}
	cub_perror(inv_map, m, NULL, !j);
}
