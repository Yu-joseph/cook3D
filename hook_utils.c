/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:34:13 by eismail           #+#    #+#             */
/*   Updated: 2025/01/28 12:36:34 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_hook(void* param)
{
	t_game* data = param;

	mouse_mv(data);
	ft_move(data);
	animation(data);
	data->x += (PLAYER / 2);
	data->y += (PLAYER / 2);
	cast_all_rays(data);
	data->x -= (PLAYER / 2);
	data->y -= (PLAYER / 2);
	draw_texture(data);
}
void ft_move(t_game *data)
{
	double newx;
	double newy;

	ft_keys(data);
	if (data->ply.movestep == 0)
	{
		data->ply.movestep = data->ply.side_direction * data->ply.move_speed;
		newx = data->player->instances->x + round(cos(data->ply.side_angle) * data->ply.movestep);
		newy = data->player->instances->y + round(sin(data->ply.side_angle) * data->ply.movestep);
	}
	else
	{
		newx = data->player->instances->x + round(cos(data->ply.rotation_angle) * data->ply.movestep);
		newy = data->player->instances->y + round(sin(data->ply.rotation_angle) * data->ply.movestep);	
	}
	if (!phaswall(newx, newy, data))
	{
		data->player->instances->x = newx;
		data->player->instances->y = newy;
	}
	data->x = data->player->instances->x;
	data->y = data->player->instances->y;
}

void mouse_mv(t_game *data)
{
    int x;
    int y;
    static int pos_x;

    mlx_get_mouse_pos(data->mlx, &x, &y);
	if (pos_x != 0)
		data->ply.rotation_angle += (x - pos_x) * 0.002;
	pos_x = x;
	norm_engle(data, &data->ply.rotation_angle);
	data->ply.side_angle = data->ply.rotation_angle + (M_PI /2);
}

void ft_keys(t_game *data)
{
	data->ply.turn_direction = 0;
	data->ply.side_direction = 0;
	data->ply.walk_direction = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->ply.walk_direction = +1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->ply.walk_direction = (-1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->ply.turn_direction = (-1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->ply.turn_direction = (+1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->ply.side_direction = (-1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->ply.side_direction = (+1);
	rebiuld(data);
	data->ply.rotation_angle += data->ply.turn_direction * data->ply.rotationSpeed;
	data->ply.side_angle += data->ply.turn_direction * data->ply.rotationSpeed;
	data->ply.movestep = data->ply.walk_direction * data->ply.move_speed;
}

void rebiuld(t_game *data)
{
	int mouse_x;
	int mouse_y;
	
	mouse_x = 0;
	mouse_y = 0;
	static int pos_x;
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	if (!haswall(data->x, data->y, data) && (mlx_is_key_down(data->mlx, MLX_KEY_S) 
		|| mlx_is_key_down(data->mlx, MLX_KEY_D) || mlx_is_key_down(data->mlx, MLX_KEY_A) 
		|| mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W) 
		|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) 
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mouse_x != pos_x))
	{
		data->color = 0;
		rectangle(data, 0, 0, W, H);
		// mlx_delete_image(data->mlx,data->line);
		// data->line = mlx_new_image(data->mlx,W, H);
		// mlx_image_to_window(data->mlx, data->line, 0, 0);
	}
	mlx_delete_image(data->mlx,data->minimap);
	data->minimap = mlx_new_image(data->mlx, MINI_W, MINI_H);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	minimap(data);
	pos_x = mouse_x;
}
