/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:24:16 by aperez-b          #+#    #+#             */
/*   Updated: 2022/01/31 12:26:35 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		cub_perror(inv_argc, NULL, NULL);
	if (!ft_strncmp(argv[1], "-h", ft_strlen(argv[1])) || \
		!ft_strncmp(argv[1], "--help", ft_strlen(argv[1])))
		cub_usage();
	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd < 0)
		cub_perror(inv_file, NULL, argv[1]);
	if (ft_strrncmp(".cub", argv[1], 4))
		cub_perror(inv_ext, NULL, NULL);
}

/* Initialize t_map with default values */
t_map	init_t_map(void)
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
	return (0);
}
