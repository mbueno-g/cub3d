/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:27:26 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/01 10:36:01 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_textures(char *trim,  t_map *m)
{
	char	**dir;
	int		w;
	
	dir = ft_split(trim, ' ');
	ft_putmatrix_fd(dir, 1,1);
	if (!dir)
	{
		free(trim);
		cub_perror(no_memory, m->map, NULL);
	}
	if (!ft_strncmp(dir[0], "NO", 3))
		m->t.north = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "SO", 3))
		m->t.south = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "WE", 3))
		m->t.west = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "EA", 3))
		m->t.east = mlx_xpm_file_to_image(m->mlx_ptr, dir[1], &w, &w);
	else if (!ft_strncmp(dir[0], "F", 2) || !ft_strncmp(dir[0], "C", 2))
		get_cf_color(dir, m);
	ft_free_matrix(&dir);
}

void	read_map(char *file, t_map *m)
{
	char	*line;
	char	*aux;
	int		fd;
	int		i;

	i = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		cub_perror(inv_file, NULL, file);
	while (1)
	{
		aux = get_next_line(fd);
		line = aux;
		if (!aux)
			break ;
		if (ft_strncmp(aux, "\n", 2))
			line = ft_strtrim(aux,"\n");
		if (ft_strncmp(aux, "\n", 2) && i <= 6 && ++i)
			check_textures(line, m);
		else
		{
			if (ft_strncmp(aux, "\n", 2) != 0 || (ft_strncmp(aux, "\n", 2) == 0 \
				&& m->height > 0))
			{
				m->map = ft_extend_matrix(m->map, line);
				if (!m->map)
					cub_perror(no_memory, NULL, NULL);
				m->height++;
			}
		}
		free(line);
	}
	close(fd);
	if (ft_matrixlen(m->map) == 0)
		cub_perror(empty_file, NULL, NULL);
	printf("Aqui empieza el mapa\n");
	ft_putmatrix_fd(m->map, 1, 1);
}

void	check_map(char *file, t_map *m)
{
	//int	j;
	//int	i;		

	read_map(file, m);
	/*j = 0;
	while (j < m->height - 1)
	{
		i = 0;
		while (m->map[i] == " ")
			i++;
		if ((ft_strlen(m->map[j + 1]) != ft_strlen(m->map[j]) && \
			ft_strchr(m->map[j + 1], '\n')) || (ft_strlen(m->map[j + 1]) != \
			ft_strlen(m->map[j]) - 1 && !ft_strchr(m->map[j + 1], '\n')))
			printf_error("the map is not a rectangle", m->map);
		j++;
	}
	m->width = ft_strlen(m->map[j - 1]);
	if (m->height < 3 && m->width < 3)
		printf_error("Map needs to be bigger than 3x3", m->map);
	check_map_characters(m, &c);
	m->charac = c;*/
}
