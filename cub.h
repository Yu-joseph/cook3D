/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:07:31 by eismail           #+#    #+#             */
/*   Updated: 2024/12/14 12:00:10 by eismail          ###   ########.fr       */
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

typedef struct s_ply_info
{
    int x;
    int y;
    int radius;
    int turn_direction;
    int walk_direction;
    int rotation_angle;
    int move_speed;
    int rotationSpeed;
}t_ply_info;

typedef struct s_game
{
    mlx_t	*mlx;
    int x;
    int y;
    int w;
    int h;
    char **map;
    t_ply_info ply;
}t_game;

#endif