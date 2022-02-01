/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <mbueno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:05:52 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/01 23:20:16 by mbueno-g         ###   ########.fr       */
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
	m->height = ft_matrixlen(m->map);
	ft_putmatrix_fd(m->map, 1, 1);
}

void	check_map(char *file, t_map *m)
{
	int	j;
	int	i;
	int	width;

	read_map(file, m);
	j = 0;
	while (j < m->height)
	{
		width = ft_strlen(m->map[j]);
		i = 0;
		if (ft_strncmp(m->map[j], "", 1) == 0)
			cub_perror(inv_map, m, NULL);	
		while (ft_isspace(m->map[j][i]) && i < width)
			i++;
		if ((j == 0 || j == m->height - 1) && ft_strchr(m->map[j], '0'))
			cub_perror(inv_wall, m, NULL);
		else if (m->map[j][0] == '0' || m->map[j][width - 1] == '0')
			cub_perror(inv_wall, m, NULL);
		j++;
	}
	if (!j)
		cub_perror(inv_map, m, NULL);
}
