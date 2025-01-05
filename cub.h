/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:07:31 by eismail           #+#    #+#             */
/*   Updated: 2025/01/05 11:22:55 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "MLX/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define CELL 30
# define PLAYER 5
# define W 1800
# define H 1300
# define FOV_ANGLE 60 * (M_PI / 180)
# define WALL_STRIP_WIDTH 4
# define NUM_RAYS 800


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

typedef struct s_game
{
    mlx_t	*mlx;
    double x;
    double y;
    int w;
    int h;
    bool down;
    bool up   ; 
    bool right ;
    bool left  ;
    char **map;
    double *rays[NUM_RAYS];
    mlx_image_t* wall;
    mlx_image_t* player;
    mlx_image_t *line;
    mlx_image_t *game;
    t_ply_info ply;
}t_game;
//ELONTUN
#endif