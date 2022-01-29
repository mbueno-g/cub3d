/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:24:16 by aperez-b          #+#    #+#             */
/*   Updated: 2022/01/28 19:46:32 by marinabuenoga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void check_file(int argc, char **argv)
{
	char	*ext;
	int		len;

	if (argc != 2)
		printf_error("Incorrect number of arguments", NULL);
	len = ft_strlen(argv[1]);
	ext = ft_substr(argv[1], len-4, len);
	if (ft_strncmp(ext,".cub", ft_strlen(ext)))
	{
		free(ext);
		printf_error("Incorrect file extension", NULL);
	}
	free(ext);
}

/* Initialize t_map with default values */
void	init_t_map(t_map *m)
{
	m->width = 0;
	m->height = 0;
	m->map = NULL;
	m->mlx_ptr = mlx_init();
}

int	main(int argc, char **argv)
{
	t_map m;

	ft_putstr_fd("Hello cub3D!\n", 1);
	check_file(argc, argv);	
	init_t_map(&m);
	check_map(argv[1], &m);

	return (0);
}
