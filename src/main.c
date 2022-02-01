/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:24:16 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/01 11:18:55 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

static void	check_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		cub_perror(inv_argc, NULL, NULL);
	if (!ft_strncmp(argv[1], "-h", 3) || \
		!ft_strncmp(argv[1], "--help", 7))
		cub_usage(0);
	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd < 0)
		cub_perror(inv_file, NULL, argv[1]);
	if (ft_strrncmp(".cub", argv[1], 4))
		cub_perror(inv_ext, NULL, NULL);
}

static t_map	init_t_map(void)
{
	t_map	m;

	m.width = 0;
	m.height = 0;
	m.map = NULL;
	m.mlx_ptr = mlx_init();
	return (m);
}

int	main(int argc, char **argv)
{
	t_map	m;

	check_file(argc, argv);
	m = init_t_map();
	check_map(argv[1], &m);
	cub_perror(end, &m, NULL);
	return (0);
}
