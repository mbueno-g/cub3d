/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:07:58 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/02/16 20:32:05 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H

# define MY_MLX_H

# include "../libft/inc/libft.h"

typedef struct s_img
{
	int		height;
	int		width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

/* Sets color for a pixel at a position in an image */
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

/* Retrieves color as int at given position from an image */
unsigned int	my_mlx_pixel_get(t_img *data, int x, int y);

/* Draws a section of a screen in a certain color */
void			my_mlx_area_put(t_img *d, t_vector p, t_vector dim, int c);

/* Loads XPM image and fills t_img struct for it */
void			mlx_load_img(void *ptr, t_img *i, char *path, int *num);

/* Writes first img to second image to given pos, ignoring "c1" pixels */
void			mlx_img_to_img(int p[2], t_img img[2], int c1);

/* Draws a vertical line: width = i, height = [j[0],j[1]) */
void			mlx_draw_vline(t_img img, int i, int j[2], int color);

#endif
