/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:24:16 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/03 16:16:13 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

static void	check_file(int argc, char **argv)
{
	int	fd;

	cub_perror(inv_argc, NULL, NULL, argc != 2);
	if (!ft_strncmp(argv[1], "-h", 3) || \
		!ft_strncmp(argv[1], "--help", 7))
		cub_usage(0);
	fd = open(argv[1], O_RDONLY);
	close(fd);
	cub_perror(inv_file, NULL, argv[1], fd < 0);
	if (ft_strrncmp(".cub", argv[1], 4))
		cub_perror(inv_ext, NULL, NULL, 1);
}

static t_map	init_t_map(void)
{
	t_map	m;

	m.width = 0;
	m.height = 0;
	m.map = NULL;
	m.dir = 'M';
	m.mlx_ptr = NULL;
	m.mlx_ptr = mlx_init();
	m.tex.north = NULL;
	m.tex.south = NULL;
	m.tex.east = NULL;
	m.tex.west = NULL;
	return (m);
}

int	main(int argc, char **argv)
{
	t_map	m;

	check_file(argc, argv);
	m = init_t_map();
	check_map(argv[1], &m);
	cub_perror(end, &m, NULL, 1);
	return (0);
}
