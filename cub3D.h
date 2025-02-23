/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:07:31 by eismail           #+#    #+#             */
/*   Updated: 2025/01/31 11:29:39 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "get/get_next_line.h"

# define CELL 20
# define PLAYER 4
# define W 1280
# define H 1100
# define MINI_W 250
# define MINI_H 250
# define FOV_ANGLE 1.0471975512 //60 * (PI / 180)
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS W
# define ANIM 14

typedef struct s_path
{
	char	*we;
	char	*no;
	char	*so;
	char	*ea;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
}			t_path;

typedef struct s_util
{
	int		j;
	int		c;
	int		i;
	int		x;
}	t_util;

typedef struct s_elem
{
	int		f;
	int		c;
	int		no;
	int		so;
	int		we;
	int		ea;
	char	*path;
}		t_elem;

typedef struct s_clr
{
	int	**ea;
	int	**we;
	int	**no;
	int	**so;
}t_clr;

typedef struct s_ply_info
{
	double	x;
	double	y;
	int		radius;
	int		turn_direction;
	int		side_direction;
	int		walk_direction;
	double	rotation_angle;
	double	side_angle;
	double	move_speed;
	double	rotationspeed;
	double	movestep;
}			t_ply_info;

typedef struct s_line
{
	int		dy;
	int		dx;
	int		steps;
	float	x_inc;
	float	y_inc;
}	t_line;

typedef struct s_texters
{
	double	x;
	double	y;
	double	distance;
	double	wall_height;
	double	angle;
	bool	vertical;
	bool	down;
	bool	up; 
	bool	right;
	bool	left;
}			t_texters;

typedef struct s_game
{
	mlx_t			*mlx;
	double			x;
	double			y;
	int				w;
	int				h;
	int				color;
	bool			down;
	bool			up; 
	bool			right;
	bool			left;
	char			**map;
	char			*ls;
	mlx_image_t		*wall;
	mlx_image_t		*player;
	mlx_image_t		*line;
	mlx_image_t		*game;
	mlx_image_t		*minimap;
	t_ply_info		ply;
	t_texters		rays[NUM_RAYS];
	mlx_image_t		*img[ANIM];
	int				frame_counter;
	t_path			*path;
	mlx_texture_t	*no;
	mlx_texture_t	*we;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_image_t		*i_no;
	mlx_image_t		*i_we;
	mlx_image_t		*i_so;
	mlx_image_t		*i_ea;
	int				f_r;
	int				f_g;
	int				f_b;
	int				c_r;
	int				c_g;
	int				c_b;
	t_clr			clr;
	mlx_image_t		*yssf;
	double			texture_step;
	double			texture_pos;
	int				img_y;
	int				img_x;
}					t_game;
/*************************/
void		fill_rays(t_game *data, double *ray, int i, double dis);
void		minimap(t_game *data);
void		ft_keys(t_game *data);
void		animation(t_game *data);
void		draw_square(void *img, int startx, int starty, int size);
int			*minimap_size(t_game *data);
void		rander_minimap(t_game *data, bool p);
void		clean_img(t_game *data);
bool		load_animation(t_game *data);
void		mouse_mv(t_game *data);
int			rgb(int r, int g, int b, int a);
void		pint_bg(t_game *data, mlx_image_t *img, double x, double y);
t_ply_info	init_ply(void);
void		ft_hook(void *param);
void		ft_move(t_game *data);
void		rebiuld(t_game *data);
void		cast_all_rays(t_game *data);
void		reander_walls(t_game *data, double **rays);
void		rectangle(t_game *data, double x, double y);
double		*cmp_hv(t_game *data, double startx, double starty, double angle);
double		*get_distance(t_game *data, double *horwallhit, double *verwallhit);
void		norm_engle(t_game *data, double *angle);
double		*wallhit(t_game *data, double xinter, double yinter, double *steps);
double		distance(double x0, double y0, double x1, double y1);
bool		haswall(double x, double y, t_game *data);
bool		phaswall(double x, double y, t_game *data);
bool		ft_mlx_init(t_game *data);
void		pint(mlx_image_t *img, int h, int w, int color);
int			ft_wedth(char **s);
int			ft_height(char **s);
/*************************/
void		parse_map(char **str, t_game *game, t_path *l);
char		**check_map(char *str, t_game *game);
bool		check_name(char *str);
int			str_cmp(char *s1, char *s2);
bool		is_redir(char c);
void		check_path(char *str, t_path *l);
int			str_long(char **str);
void		draw_texture(t_game *data);
int			**get_pixels(mlx_image_t *img);
void		free_d(char **t);
void		free_path(t_path *p, t_game *game);
void		load_img(t_game *game, t_path *l);
int			**get_pixels(mlx_image_t *img);
mlx_image_t	*get_texture(t_game *data, int ***clr, int i);
void		draw_wall(t_game *data, double t_pix, double b_pix, int i);
bool		check_rest(char *str);
int			count_lingth(char *str, char c);
bool		is_valid(char c);
void		check_li(char *line, char *str);
char		**check_map(char *str, t_game *game);
void		map_checker(char **str, int j, int i);
bool		check_elem(t_elem *elem);
void		init_elem(t_elem *elem);
bool		fill_elem(char *str, t_elem *elem, t_path *l);
void		skip_sp(char **str);
int			line_parse(char **str, t_game *g, int j, int c);
void		init_util(t_util *t);
bool		some_err(char c, t_util t);
void		handle_map(char **str);
void		check_number(char **c, t_path *l, char *str);
void		fill_path(char *s, char *l, t_path *p);
void		handle_redir(char *str, t_path *s);
void		free_d(char **t);
#endif
