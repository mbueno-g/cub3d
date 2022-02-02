/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:10:05 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/02 23:16:16 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_perror(t_cub_err err, t_map *m, char *param)
{
	cub_end(m);
	ft_putstr_fd("cub3d: ", 2);
	write(2, "invalid number of arguments\n", 28 * (err == inv_argc));
	write(2, "file must be of .cub type\n", 26 * (err == inv_ext));
	write(2, "error opening file: ", 20 * (err == inv_file));
	write(2, "file is empty\n", 14 * (err == empty_file));
	write(2, "devide out of memory\n", 21 * (err == no_memory));
	write(2, "invalid color: ", 15 * (err == inv_color));
	write(2, "map not surrounded by walls\n", 28 * (err == inv_wall));
	write(2, "invalid map\n", 12 * (err == inv_map));
	write(2, "invalid character\n", 18 * (err == inv_charac));
	ft_putendl_fd(param, 2);
	if (err == inv_argc && ft_putchar_fd('\n', 2))
		cub_usage(1);
	if (err == end)
		exit(0);
	exit(1);
}

void	cub_usage(int errno)
{
	ft_putstr_fd("Cub3D\nA simple raycaster with MinilibX\n\n", 2);
	ft_putstr_fd("usage: cub3d <map_file.cub>\n", 2);
	exit(errno);
}
