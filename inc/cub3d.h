/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:25:42 by aperez-b          #+#    #+#             */
/*   Updated: 2022/01/29 18:20:47 by marinabuenoga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../get_next_line/get_next_line.h"

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_color
{
	int red;
	int green;
	int blue;
}			  t_color;

typedef struct s_texture
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	t_color *floor;
	t_color	*ceiling;
}			  t_texture;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	void		*mlx_ptr;
	t_texture	*t;
}			  t_map;


void check_map(char *file, t_map *m);

void printf_error(char *message, char **str);

#endif
