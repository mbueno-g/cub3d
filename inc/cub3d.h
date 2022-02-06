/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:25:42 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/06 21:17:46 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../get_next_line/get_next_line.h"

# include <mlx.h>
# include "my_mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef enum e_cub_err
{
	end,
	inv_argc,
	inv_ext,
	inv_file,
	empty_file,
	no_memory,
	inv_color,
	inv_wall,
	inv_map,
	inv_charac,
	inv_player,
	inv_tex
}				t_cub_err;

typedef struct s_color
{
	short	t;
	short	r;
	short	g;
	short	b;
}				t_color;

typedef struct s_tex
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	int		hex_floor;
	int		hex_ceiling;
}				t_tex;

typedef struct s_player
{
	t_vector	v;
	char		dir;
}				t_player;

typedef struct s_map
{
	int			fd;
	char		**map;
	int			height;
	int			width;
	void		*mlx_ptr;
	void		*win_ptr;
	t_tex		tex;
	t_player	pl;
}				t_map;

typedef struct s_data
{
	int		angle;
	int		hfov;
	int		width;
	int		height;
	int		ray_angle;
	float	incre_angle;
	float	x;
	float	y;
	int		precision;
	t_img	i;
}				t_data;


/* Check possible map errors */
void	check_map(char *file, t_map *m);

/* Prints appropriate error message and exits, freeing everything */
int		cub_perror(t_cub_err err, t_map *m, char *param, int c);

/* Prints usage for the cub3D program */
void	cub_usage(int errno);

/* Atoi for colors */
int		cub_atoi(const char *nptr, short *nbr);

/* Fill color int */
void	get_cf_color(char **dir, t_map *m);

/* Frees all necessary things before exiting */
void	cub_end(t_map *m);

/* Initialize game */
void	game_init(t_map *m);

/* Draw game */
void	draw_game(t_map *m);

/* Converts degrees to radius */
float	degree_to_radians(int degree);

#endif
