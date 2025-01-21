/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:07:31 by eismail           #+#    #+#             */
/*   Updated: 2025/01/07 10:48:31 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "gnl/get_next_line.h"
# include "MLX/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>


#include <stdio.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "get/get_next_line.h"

# define CELL 10
# define PLAYER 2
# define W 2500
# define H 1300
# define MINI_W 320
# define MINI_H 200
# define FOV_ANGLE 60 * (M_PI / 180)
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS 2500


typedef struct s_path
{
    char *WE;
    char *NO;
    char *SO;
    char *EA;
}   t_path;

typedef struct s_util
{
	int		j;
	int		c;
	int		i;
	int		x;
}	t_util;

typedef struct s_elem
{
	int	f;
	int	c;
	int	no;
	int	so;
	int	we;
	int	ea;
	char	*path;
}	t_elem;


typedef struct s_clr
{
    int **ea;
    int **we;
    int **no;
    int **so;
}t_clr;


typedef struct s_ply_info
{
    double x;
    double y;
    int radius;
    int turn_direction;
    int side_direction;
    int walk_direction;
    double rotation_angle;
    double side_angle;
    double move_speed;
    double rotationSpeed;
    double movestep;
}t_ply_info;

typedef struct s_texters
{
    double  x;
    double  y;
    double  distance;
    double  wall_height;
    double  angle;
    bool    vertical;
    bool    down;
    bool    up   ; 
    bool    right ;
    bool    left  ;
}t_texters;

typedef struct s_game
{
    mlx_t	*mlx;
    double x;
    double y;
    int w;
    int h;
    int color;
    bool down;
    bool up   ; 
    bool right ;
    bool left  ;
    char **map;
    char *ls;
    mlx_image_t* wall;
    mlx_image_t* player;
    mlx_image_t *line;
    mlx_image_t *game;
    t_ply_info ply;
    t_texters rays[NUM_RAYS];
    /******/
    // int p;
    mlx_texture_t			*no;
	mlx_texture_t			*we;
	mlx_texture_t			*so;
	mlx_texture_t			*ea;
    mlx_image_t             *i_no;
    mlx_image_t             *i_we;
    mlx_image_t             *i_so;
    mlx_image_t             *i_ea;
    t_clr                   clr;
    mlx_image_t             *yssf;
}t_game;
/*************************/
void mouse_mv(t_game *data);
int rgb(int r, int g, int b, int a);
void pint_bg(mlx_image_t *img, double x, double y);
t_ply_info init_ply();
char **get_map(char *file);
void ft_hook(void* param);
void ft_move(t_game *data);
void rebiuld(t_game *data);
void cast_all_rays(t_game *data);
void reander_walls(t_game *data, double **rays);
void rectangle(t_game *data, double x, double y, double width, double height);
double *cmp_hv(t_game *data, double startx,double starty, double angle);
double *get_distance(t_game *data, double *horwallhit, double *verwallhit);
void norm_engle(t_game *data, double *angle);
double* ft_vertical(t_game *data, double startx, double starty, double angl);
double *wallhit(t_game *data, double xinter, double yinter , double xstep, double ystep);
double distance(double x0, double y0, double x1,double y1);
bool haswall(double x, double y, t_game *data);
bool phaswall(double x, double y, t_game *data);
void draw_line(mlx_image_t *mlx, int x0, int y0, int x1, int y1, int color);
void ft_mlx_init(t_game *data);
void pint(mlx_image_t *img, int h, int w, int color);
int	ft_wedth(char **s);
int	ft_height(char **s);
int cross(t_game *data);
int close_window(int keycode, void *param);
/*************************/
void	parse_map(char **str, t_game *game, t_path *l);
char	**check_map(char *str, t_game *game);
bool	check_name(char *str);
int		str_cmp(char *s1, char *s2);
bool	is_redir(char c);
void	check_path(char *str, t_path *l);
int		str_long(char **str);
void draw_texture(t_game *data);
int	**get_pixels(mlx_image_t *img);
// void    draw_texter(t_game *data);
#endif