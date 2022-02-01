/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:10:05 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/01 11:07:00 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_perror(t_cub_err err, t_map *m, char *param)
{
	cub_end(m);
	ft_putstr_fd("cub3d: ", 2);
	if (err == inv_argc)
		ft_putstr_fd("invalid number of arguments\n", 2);
	if (err == inv_ext)
		ft_putstr_fd("file must be of .cub type\n", 2);
	if (err == inv_file)
		ft_putstr_fd("error opening file: ", 2);
	if (err == empty_file)
		ft_putstr_fd("file is empty\n", 2);
	if (err == no_memory)
		ft_putstr_fd("device out of memory\n", 2);
	if (err == inv_color)
		ft_putstr_fd("invalid color: ", 2);
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
