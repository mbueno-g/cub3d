/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:25:42 by aperez-b          #+#    #+#             */
/*   Updated: 2022/01/31 17:46:36 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../get_next_line/get_next_line.h"

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_cub_err
{
	inv_argc,
	inv_ext,
	inv_file,
	empty_file,
	no_memory,
	inv_color
}				t_cub_err;

typedef struct s_color
{
	short t;
	short r;
	short g;
	short b;
}				t_color;

typedef struct s_texture
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
}				t_texture;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	void		*mlx_ptr;
	int			hex_floor;
	int			hex_ceiling;
	t_texture	t;
}				t_map;

/* Check possible map errors */
void	check_map(char *file, t_map *m);

/* Prints appropriate error message and exits */
void	cub_perror(t_cub_err err, char **str, char *param);

/* Prints usage for the cub3D program */
void	cub_usage(int errno);

/* Atoi for colors */
int		cub_atoi(const char *nptr, short *nbr);

/* Fill color int */
void	get_cf_color(char **dir, t_map *m);

#endif