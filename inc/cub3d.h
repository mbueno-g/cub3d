/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:25:42 by aperez-b          #+#    #+#             */
/*   Updated: 2022/02/11 20:21:51 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/inc/libft.h"
# include "keycodes.h"
# include "../get_next_line/get_next_line.h"

# include <mlx.h>
# include "my_mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# ifndef WIN_H
#  define WIN_H 480
# endif

# ifndef WIN_W
#  define WIN_W 640
# endif

# ifndef SIZE
#  define SIZE 7
# endif

/* Enum to handle various exit/error messages */
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

/* Struct to handle rgb colors with transparency */
typedef struct s_color
{
	short	t;
	short	r;
	short	g;
	short	b;
}				t_color;

/* Every image corresponding to a wall texture, plus floor and ceiling */
typedef struct s_tex
{
	t_img	n;
	t_img	s;
	t_img	w;
	t_img	e;
	int		floor;
	int		ceiling;
}				t_tex;

/* Struct to store various attributes of our player */
typedef struct s_player
{
	float	x;
	float	y;
	float	oldx;
	float	oldy;
	char	dir;
	float	speed;
}				t_player;

/* Struct to store all ray-casting-related data */
typedef struct s_ray
{
	float	incre_angle;
	float	angle;
	float	oldangle;
	float	hfov;
	int		width;
	int		height;
	float	lim;
	int		precision;
}				t_ray;

/* Handles most game attributes */
typedef struct s_game
{
	int			fd;
	char		**map;
	int			height;
	int			width;
	int			mouse_x;
	long		nframes;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		win_img;
	t_img		minimap;
	t_img		scope;
	t_tex		tex;
	t_ray		ray;
	t_player	pl;
	float	x;
	float	y;
}				t_game;

/* Check possible map errors */
void	check_map(char *file, t_game *g);

/* Prints appropriate error message and exits, freeing everything */
int		cub_perror(t_cub_err err, t_game *g, char *param, int c);

/* Prints usage for the cub3D program */
void	cub_usage(int errno);

/* Function called by mlx when exiting */
int		cub_exit(void *param);

/* Atoi for colors (more restrictive than original) */
int		cub_atoi(const char *nptr, short *nbr);

/* Fills color int for floor and ceiling */
void	get_cf_color(char **dir, t_game *g);

/* Frees all necessary things before exiting */
void	cub_end(t_game *g);

/* Initializes game */
void	game_init(t_game *g);

/* Draws game */
void	draw_game(t_game *g);

/* Initialize raycast data */
void	init_ray(t_game *g);

/* Converts degrees to radians */
float	degree_to_radians(float degree);

/* Draws a 2D minimap at the bottom right of the screen */
void	cub_minimap(t_game *g);

/* Function to shoot rays in a given direction to find walls */
void	cub_raycast(t_game *g);

/* Function called inside mlx loop */
int		cub_update(void *param);

/* Checks if there're c's in position range [n0,n1] of m */
int		checkcn(char *m, char c, int n0, int n1);

/* Check every element of the map: spaces + characters */
void	check_elements(t_game *g, int j);

#endif
