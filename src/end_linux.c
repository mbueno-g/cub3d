/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_linux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:06:18 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/01 11:09:51 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cub_end(t_map *m)
{
	if (m)
	{
		ft_free_matrix(&m->map);
		close(m->fd);
		mlx_destroy_image(m->mlx_ptr, m->tex.north);
		mlx_destroy_image(m->mlx_ptr, m->tex.south);
		mlx_destroy_image(m->mlx_ptr, m->tex.east);
		mlx_destroy_image(m->mlx_ptr, m->tex.west);
		mlx_destroy_display(m->mlx_ptr);
		free(m->mlx_ptr);
	}
}
