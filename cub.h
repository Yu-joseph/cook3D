/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:07:31 by eismail           #+#    #+#             */
/*   Updated: 2024/12/18 13:05:50 by eismail          ###   ########.fr       */
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
# define MINI_W 320
# define MINI_H 200
# define FOV_ANGLE 60 * (M_PI / 180)
# define WALL_STRIP_WIDTH 4
# define NUM_RAYS 30


typedef struct s_ply_info
{
    int x;
    int y;
    int radius;
    int turn_direction;
    int walk_direction;
    double rotation_angle;
    double move_speed;
    double rotationSpeed;
}t_ply_info;

typedef struct s_game
{
    mlx_t	*mlx;
    int x;
    int y;
    int w;
    int h;
    bool down;
    bool up   ; 
    bool right ;
    bool left  ;
    char **map;
    mlx_image_t* wall;
    mlx_image_t* player;
    mlx_image_t *line;
    t_ply_info ply;
}t_game;

#endif