/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marinabuenogarcia <mbueno-g@student.42.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:27:12 by marinabuenoga     #+#    #+#             */
/*   Updated: 2022/01/29 19:04:44 by marinabuenoga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void check_textures(char *line, t_map *m)
{
	char	*dir;
	char	*path;
	int		w;
	int		h;
	//char	*c;

	dir = ft_substr(line, 0, 2);
	path = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(dir, "NO", ft_strlen(dir)) == 0)
		m->t->north =  mlx_xpm_file_to_image(m->mlx_ptr, path , &w, &h);
	/*else if (ft_strncmp(dir, "SO", ft_strlen(dir)) == 0)
		m->t->south = mlx_xpm_file_to_image(m->mlx_ptr, path, NULL, NULL);
	else if (ft_strncmp(dir, "WE", ft_strlen(dir)) == 0)
		m->t->west = mlx_xpm_file_to_image(m->mlx_ptr, path, NULL, NULL);
	else if (ft_strncmp(dir, "EA", ft_strlen(dir)) == 0)
		m->t->east = mlx_xpm_file_to_image(m->mlx_ptr, path, NULL, NULL);*/
	/*else
	{
		c = ft_substr(dir, 0,1);
		//if (ft_strcmp(c, "F", 1) == 0)
		//	fill_colo()	
		//else if (ft_strncmp(c, "C", 1) == 0)

	}*/
	//free(dir);
	//free(path);
}

void	ft_create_map(int fd, t_map *m, char *line)
{
	int	i;

	m->map = malloc(sizeof(char *) * (m->height));
	if (!m->map)
		printf_error("Malloc failed", NULL);
	i = 0;
	while (1)
	{
		m->map[i] = NULL;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (i <= 7)
			check_textures(line, m);
		m->map[i] = ft_substr(line, 0, ft_strlen(line));
		free(line);
		i++;
	}
	close(fd);
	m->map[i] = NULL;
}

void	read_map(char *file, t_map *m)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		printf_error("Missing file", NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		m->height++;
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		printf_error("Missing file", NULL);
	if (m->height == 0)
		printf_error("Empty file", NULL);
	m->height -= 8;
	ft_create_map(fd, m, NULL);
}

/* Check possible map errors */
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
