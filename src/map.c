/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:27:26 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/01 11:22:56 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_textures(char *trim, t_map *m)
{
	char	**dir;
	int		w;

	dir = ft_split(trim, ' ');
	ft_putmatrix_fd(dir, 1, 1);
	if (!dir)
	{
		free(trim);
		cub_perror(no_memory, m, NULL);
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
	if (m->fd < 0)
		cub_perror(inv_file, m, file);
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
	ft_putstr_fd("-------------\n", 1);
	if (!i)
		cub_perror(empty_file, m, NULL);
	ft_putmatrix_fd(m->map, 1, 1);
}

void	check_map(char *file, t_map *m)
{
	int	j;
	int	i;

	read_map(file, m);
	j = 0;
	while (j < m->height - 1)
	{
		i = 0;
		while (m->map[i][j] == ' ')
			i++;
		if ((ft_strlen(m->map[j + 1]) != ft_strlen(m->map[j]) && \
			ft_strchr(m->map[j + 1], '\n')) || (ft_strlen(m->map[j + 1]) != \
			ft_strlen(m->map[j]) - 1 && !ft_strchr(m->map[j + 1], '\n')))
			cub_perror(inv_ext, m, NULL);
		j++;
	}
	if (m->height < 3 && m->width < 3)
		cub_perror(inv_ext, m, NULL);
}
