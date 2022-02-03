/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:07:58 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/03 18:57:38 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

/* mlx_pixel_put but faster */
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

unsigned int     my_mlx_pixel_get(t_img *data, int x, int y);

#endif
