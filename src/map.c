/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <mbueno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:05:52 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/21 16:48:04 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_list	*get_anim(t_img *img, t_list **anim, int n[0][2])
{
	if (n && anim && *anim && img)
		(*n)[0]--;
	if (!img)
		return (*anim);
	if (!img->i)
	{
		free(img);
		(*n)[1] = 0;
		return (*anim);
	}
	ft_lstadd_back(anim, ft_lstnew(img));
	return (*anim);
}

void	check_textures(char *trim, t_game *g, int n[0][2])
{
	char	**dir;

	dir = ft_split(trim, ' ');
	if (!dir)
	{
		free(trim);
		cub_perror(no_memory, g, NULL, 1);
	}
	if (!ft_strncmp(dir[0], "NO", 3))
		g->tex.n_bak = get_anim(mlx_load_img(g->mlx_ptr, dir[1]), &g->tex.n, n);
	else if (!ft_strncmp(dir[0], "SO", 3))
		g->tex.s_bak = get_anim(mlx_load_img(g->mlx_ptr, dir[1]), &g->tex.s, n);
	else if (!ft_strncmp(dir[0], "EA", 3))
		g->tex.e_bak = get_anim(mlx_load_img(g->mlx_ptr, dir[1]), &g->tex.e, n);
	else if (!ft_strncmp(dir[0], "WE", 3))
		g->tex.w_bak = get_anim(mlx_load_img(g->mlx_ptr, dir[1]), &g->tex.w, n);
	else if ((!ft_strncmp(dir[0], "F", 2) && g->tex.floor == -1) || \
		(!ft_strncmp(dir[0], "C", 2) && g->tex.ceiling == -1))
		get_cf_color(dir, g);
	else
	{
		ft_free_matrix(&dir);
		cub_perror(inv_map, g, NULL, 1);
	}
	ft_free_matrix(&dir);
}

void	read_map(char *file, t_game *g)
{
	char	*line[2];
	int		n[2];

	n[0] = -1;
	n[1] = -1;
	g->fd = open(file, O_RDONLY);
	cub_perror(inv_file, g, file, g->fd < 0);
	while (1)
	{
		line[0] = get_next_line(g->fd);
		if (!line[0])
			break ;
		line[1] = ft_strtrim(line[0], "\n");
		free(line[0]);
		if (line[1] && line[1][0] && ++n[0] < 6)
			check_textures(line[1], g, &n);
		else if ((line[1] && line[1][0]) || n[0] >= 6)
			g->map = ft_extend_matrix(g->map, line[1]);
		if ((int)ft_strlen(line[1]) > g->width)
			g->width = ft_strlen(line[1]);
		free(line[1]);
	}
	cub_perror(empty_file, g, NULL, !n[0]);
	cub_perror(inv_tex, g, NULL, !n[1]);
	g->height = ft_matrixlen(g->map);
}

void	check_map(t_game *g)
{
	int	j;
	int	i;
	int	w;

	j = -1;
	while (++j < g->height)
	{
		w = ft_strlen(g->map[j]) - 1;
		i = 0;
		while (g->map[j][i] == ' ' && i <= w)
			i++;
		while (g->map[j][w] == ' ' && w > 0)
			w--;
		if (ft_strncmp(g->map[j], "", 1) == 0)
			cub_perror(inv_map, g, NULL, 1);
		if ((j == 0 || j == g->height - 1) && ft_strlen(g->map[j]) - \
			ft_countchar(g->map[j], ' ') - ft_countchar(g->map[j], '1'))
			cub_perror(inv_wall, g, NULL, 1);
		else if (w > i && (g->map[j][i] != '1' || g->map[j][w] != '1'))
			cub_perror(inv_wall, g, NULL, 1);
	}
	check_elements(g);
	cub_perror(inv_map, g, NULL, !j);
}
